// TestBlock2.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "math.h"
#include "stdlib.h"
#include <stdio.h>
#include "assert.h"

#include "PsimBlock.h"
#include "psimutil.h"



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


void REQUESTUSERDATA(int nRequestReason,
					 int nRequestCode, 
					 int nRequestParam, 
					 void ** ptrUserData,
					 int * pnParam1, 
					 int * pnParam2, 
					 char * szParam1, 
					 char * szParam2
					)
{
	//Parameters and Input/output nodes do not depend on input file. They are always the same.


	if( nRequestCode == REQUEST_PARAM_COUNT )
	{
		//Get the number of parameters
		// int * pnParam1:  returns the number of parameters excluding a Data File name parameter.
		// int * pnParam2:  1: Data File parameter exist (only one Data File parameter is allowed)   0: no Data File parameter
		*pnParam1 = 3; // 3 parameters
		*pnParam2 = 1; // Data File parameter.
	}
	else if( nRequestCode == REQUEST_DATAFILE_INFO )
	{
		// Get Data File parameter information
		// char * szParam1: Node Label  20 characters maximum.
		// int * pnParam1:  1: Show Display check box     0: Do not show Display check box
		// int * pnParam2:  if *pnParam1 == 1  then:   1: Display check box is checked by default.     0: Display check box is not checked by default
		strcpy(szParam1, "Input Data File"); //Label
		*pnParam1 = 1; // Show Display check box
	}
	else if(nRequestCode == REQUEST_PARAM_INFO)
	{
		// Get parameter information
		// char * szParam1: Node Label  20 characters maximum.
		// char * szParam2: Node default value  50 characters maximum.
		// int * pnParam1:  1: Show Display check box     0: Do not show Display check box
		// int * pnParam2:  if *pnParam1 == 1  then:   1: Display check box is checked by default.     0: Display check box is not checked by default
		int nParam = nRequestParam;
		switch(nParam)						
		{
			//Three Parameters 
			case 0:
				strcpy(szParam1, "Moving Avg. Samples");
				*pnParam1 = 1; // Show Display check box
				if( nRequestReason == ACTION_DLL_SELECTED) //new element. Set default value
				{
					strcpy(szParam2, "3");
				}
				break;
				
			case 1:
				strcpy(szParam1, "Multiplier");
				*pnParam1 = 1; // Show Display check box
				if( nRequestReason == ACTION_DLL_SELECTED) //new element. Set default value
				{
					strcpy(szParam2, "3.14");
				}
				break;

			case 2:
				strcpy(szParam1, "Output File Name");
				*pnParam1 = 0; // Show Display check box
				if( nRequestReason == ACTION_DLL_SELECTED) //new element. Set default value
				{
					strcpy(szParam2, "data.out");
				}
				break;

			default:
				assert(0);
				break;
		}
	}
	else if( nRequestCode == REQUEST_IN_OUT_NODES )
	{
		// Get the number of Input and Output nodes
		// int * pnParam1:  returns the number of input nodes.
		// int * pnParam2:  returns the number of output nodes.
		*pnParam1 = 1; // input nodes
		*pnParam2 = 2; // output nodes
	}
	else if(nRequestCode == REQUEST_INPUT_NODE_INFO)
	{
		// Get Input node information
		// char * szParam1: Node Label  20 characters maximum.
		int nNode = nRequestParam;
		switch(nNode)
		{
			//one input node only
			case 0:
				strcpy(szParam1, "input");
				break;

			default:
				assert(0);
				break;

		}

	}
	else if(nRequestCode == REQUEST_OUTPUT_NODE_INFO)
	{
		// Get Output node information
		// char * szParam1: Node Label  20 characters maximum.
		int nNode = nRequestParam;
		switch(nNode)						
		{
			//two output nodes 
			case 0:
				strcpy(szParam1, "o1");
				break;

			case 1:
				strcpy(szParam1, "o2");
				break;

			default:
				assert(0);
				break;
		}
	}
}




////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// Simulation Functions

struct Internal_DLL_Block_Data
{

	int m_nStepCount;
	
	int m_nInputNodes;
	int m_nOutputNodes;


	int m_nMovingAverageSamples;
	double m_fMultiplier;

	double * m_pSampleData;



	char m_szInputFile[260];
	char m_szOutputFile[260];


	FILE * m_inputStream;
	FILE * m_outputStream;

};


void OPENSIMUSER(const char *szId, const char * szNetlist, void ** ptrUserData, int *pnError, LPSTR szErrorMsg, void * pPsimParams)
{

	EXT_FUNC_PSIM_INFO * pPsimInfo = (EXT_FUNC_PSIM_INFO *)pPsimParams;


	assert(*ptrUserData == NULL);
	*ptrUserData = new Internal_DLL_Block_Data;

	Internal_DLL_Block_Data * pData = (Internal_DLL_Block_Data *)(*ptrUserData);
	memset(pData, 0, sizeof(Internal_DLL_Block_Data) );

	
	CNetListParams netlist;

	netlist.parse_netlist(szNetlist);


	assert( strcmp(netlist[0],"DLL_EXT") == 0 );
	assert( strcmp(netlist[1], szId) == 0 );
	
	pData->m_nInputNodes  = atoi(netlist[2]); //number of input nodes
	pData->m_nOutputNodes = atoi(netlist[3]); //number of output nodes

	// netlist[4] : DLL FilePath
	
	int nParamStartIndex = 5 + pData->m_nInputNodes + pData->m_nOutputNodes;

	// value of parameter 1
	pData->m_nMovingAverageSamples = atoi( netlist[nParamStartIndex] );
	if( pData->m_nMovingAverageSamples < 3 )
	{
		pData->m_nMovingAverageSamples = 3;
	}
	if( pData->m_nMovingAverageSamples > 100 )
	{
		pData->m_nMovingAverageSamples = 100;
	}
	pData->m_pSampleData = new double[pData->m_nMovingAverageSamples];
	int nCtr;
	for(nCtr=0; nCtr<pData->m_nMovingAverageSamples; nCtr++)
	{
		pData->m_pSampleData[nCtr] = 0;
	}


	// value of parameter 2
	pData->m_fMultiplier = atof( netlist[nParamStartIndex+1] );
	

	strcpy( pData->m_szOutputFile, netlist[nParamStartIndex+2] );

	// Input file is always the last parameter in the netlist
	strcpy( pData->m_szInputFile, netlist[ netlist.GetCount() - 1 ] );


	if( GetFileAttributes(pData->m_szInputFile) != 0XFFFFFFFF )
	{	// if file Exist

		if(strchr(pData->m_szOutputFile, '\\') == NULL) 
		{
			// if OutputFile does not have path information, add Input file path to output file
			char szBuffer[260];
			strncpy(szBuffer, pData->m_szInputFile, DWORD(strrchr(pData->m_szInputFile, '\\')) - DWORD(pData->m_szInputFile) + 1);
			szBuffer[DWORD(strrchr(pData->m_szInputFile, '\\')) - DWORD(pData->m_szInputFile) + 1] = '\0';
			strcat(szBuffer, pData->m_szOutputFile);
			strcpy(pData->m_szOutputFile, szBuffer);
		}

		pData->m_inputStream = fopen( pData->m_szInputFile, "r" );
		if( pData->m_inputStream == NULL )
		{
			sprintf(szErrorMsg, "Unable to open file %s", pData->m_szInputFile);
			*pnError = 1; //Error
			return;
		}
		
		
		pData->m_outputStream = fopen( pData->m_szOutputFile, "w+" );
		if( pData->m_outputStream == NULL )
		{
			sprintf(szErrorMsg, "Unable to open file %s", pData->m_szOutputFile);
			*pnError = 1; //Error
			return;
		}
	}



	
	*pnError = 0; //Success
}



void RUNSIMUSER(double t, double delt, double *in, double *out, void ** ptrUserData, int *pnError, LPSTR szErrorMsg)
{
	Internal_DLL_Block_Data * pData = (Internal_DLL_Block_Data *)(*ptrUserData);

	if( pData == NULL)
	{
		return;
	}


	char szBuffer[100];
	
	// DLL has 1 input and 2 output ( in[0] and out[0], out[1] )

	//output1 is Moving average of input1 going back m_nMovingAverageSamples number of data
	int nCtr;
	for(nCtr=pData->m_nMovingAverageSamples-2; nCtr>=0; nCtr--)
	{
		pData->m_pSampleData[nCtr+1] = pData->m_pSampleData[nCtr];
	}
	pData->m_pSampleData[0] = in[0];

	double fOut1 = 0;
	for(nCtr=0; nCtr<pData->m_nMovingAverageSamples; nCtr++)
	{
		fOut1 += pData->m_pSampleData[nCtr];
	}
	fOut1 /= pData->m_nMovingAverageSamples;
	out[0] = fOut1;

	
	//output2 is the value at the next line of input file * m_fMultiplier
	double fValueFromFile = 0.0;
	if( pData->m_inputStream != NULL )
	{
		
		if( fgets( szBuffer, 100, pData->m_inputStream ) == NULL )
		{
			//Assume end-of-file

			fclose(pData->m_inputStream);
			pData->m_inputStream = NULL;
		}
		else
		{
			fValueFromFile = atof(szBuffer);
		}
	}

	out[1] = fValueFromFile * pData->m_fMultiplier;
	
	pData->m_nStepCount++;
	
	sprintf(szBuffer, "%i) %g,%g,%g\n", pData->m_nStepCount, in[0], out[0], out[1]);
	fputs(szBuffer, pData->m_outputStream);
	fflush(pData->m_outputStream);
	
	

	*pnError = 0; //Success
}


void CLOSESIMUSER(const char *szId, void ** ptrUserData)
{
	Internal_DLL_Block_Data * pData = (Internal_DLL_Block_Data *)(*ptrUserData);
	assert(*ptrUserData != NULL);
	if( pData == NULL )
	{
		return;
	}

	if( pData->m_inputStream != NULL )
	{
		fclose(pData->m_inputStream);
		pData->m_inputStream = NULL;
	}
	if( pData->m_outputStream != NULL )
	{
		fclose(pData->m_outputStream);
		pData->m_outputStream = NULL;
	}



	delete pData;
	*ptrUserData = NULL;
}


