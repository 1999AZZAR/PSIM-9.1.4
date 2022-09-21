// TestBlock.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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
#define MyApp_VERSION  "1.2"


class Internal_DLL_Block_RuntimeData
{
public:
	Internal_DLL_Block_RuntimeData()
	{
		memset(m_szInputFile, 0, 260);
		m_nInputNodes = 0;
		m_nOutputNodes = 0;
		
		m_arrayInputNodes = NULL;
		m_arrayOutputNodes = NULL;
	}

	virtual ~Internal_DLL_Block_RuntimeData()
	{
		Clear();
	}

	void Clear()
	{
		if( m_arrayInputNodes != NULL )
		{
			for(int nCtr=0; nCtr<m_nInputNodes; nCtr++)
			{
				if( m_arrayInputNodes[nCtr] != NULL )
				{
					delete [] m_arrayInputNodes[nCtr];
				}
			}
			delete [] m_arrayInputNodes;
		}
		if( m_arrayOutputNodes != NULL )
		{
			for(int nCtr=0; nCtr<m_nOutputNodes; nCtr++)
			{
				if( m_arrayOutputNodes[nCtr] != NULL )
				{
					delete [] m_arrayOutputNodes[nCtr];
				}
			}
			delete [] m_arrayOutputNodes;
		}
	}


	BOOL LoadFile(char * szFilePath)
	{
 		char szTemp[300];

		if( GetFileAttributes(szFilePath) == 0XFFFFFFFF )
		{ //File does not exist
			sprintf(szTemp, "File does not Exist.\r\nFilename: %s", szFilePath);
			::MessageBox(NULL, szTemp, "My Program", MB_OK);
			return FALSE;
		}


		//Open selected file.
		FILE * inputStream = fopen( szFilePath, "r" );
		if( inputStream == NULL )
		{ //Reject file if can not open
			sprintf(szTemp, "Failed to open file.\r\nFilename: %s", szFilePath);
			::MessageBox(NULL, szTemp, "My Program", MB_OK);
			return FALSE;
		}

		
		//Delete previously allocated memory for m_arrayInputNodes and m_arrayOutputNodes
		Clear();

		//Read input and output nodes from file.
		int nCtr = 0;
		int i = 0;
		while( fgets( szTemp, 100, inputStream ) != NULL )
		{
			i = 0;
			// Trim input and use  ;   for comment
			while( (szTemp[i] != '\0') && (szTemp[i] != ';') )
			{
				i++;
			}
			i--;
			while( (i >= 0) && 
				   ((szTemp[i] == ' ') || (szTemp[i] == '\t') || (szTemp[i] == '\r') || (szTemp[i] == '\n') )
				 )
			{
				i--;
			}
			szTemp[i+1] = '\0';



			nCtr++;
			if( nCtr == 1 )
			{	//Get number of input nodes from file
				m_nInputNodes = atoi(szTemp);
				if(m_nInputNodes > 0)
				{
					m_arrayInputNodes = new LPSTR[m_nInputNodes];
					memset(m_arrayInputNodes, 0, sizeof(LPSTR) * m_nInputNodes);
				}
			}
			else if( nCtr == 2 )
			{
				//Get number of output nodes from file
				m_nOutputNodes = atoi(szTemp);
				if(m_nOutputNodes > 0)
				{
					m_arrayOutputNodes = new LPSTR[m_nOutputNodes];
					memset(m_arrayOutputNodes, 0, sizeof(LPSTR) * m_nOutputNodes);
				}
			}
			else if( (nCtr >= 3) && (nCtr < (3 + m_nInputNodes) ) )
			{
				//Get input node labels from file
				m_arrayInputNodes[nCtr-3] = new char[strlen(szTemp)+2];
				strcpy(m_arrayInputNodes[nCtr-3], szTemp);
			}
			else if( (nCtr >= (3 + m_nInputNodes)) && (nCtr < (3 + m_nInputNodes + m_nOutputNodes) ) )
			{
				//Get output node labels from file
				m_arrayOutputNodes[nCtr-(3+m_nInputNodes)] = new char[strlen(szTemp)+2];
				strcpy(m_arrayOutputNodes[nCtr-(3+m_nInputNodes)], szTemp);
			}
			else
			{
				//...
			}
		}
		//end-of-file
		fclose(inputStream);
		inputStream = NULL;

		if( ( (m_nInputNodes == 0) && (m_nInputNodes == 0) )  || 
			(nCtr < (2 + m_nInputNodes + m_nOutputNodes) ) 
		  )
		{
			// file was not good
			return FALSE;
		}

		//keep a copy of input file path
		strcpy(m_szInputFile, szFilePath);
		
		return TRUE;
	}
	
	char * GetInputNodeLabel(int nIndex) // nIndex: Zero based index
	{
		if( (m_arrayInputNodes != NULL) && 
			( (nIndex >= 0) && (nIndex < m_nInputNodes) ) &&
			(m_arrayInputNodes[nIndex] != NULL)
		  )
		{
			return m_arrayInputNodes[nIndex];
		}
		else
		{
			return m_emptyNode;
		}
	}

	char * GetOutputNodeLabel(int nIndex) // nIndex: Zero based index
	{
		if( (m_arrayOutputNodes != NULL) && 
			( (nIndex >= 0) && (nIndex < m_nOutputNodes) ) &&
			(m_arrayOutputNodes[nIndex] != NULL)
		  )
		{
			return m_arrayOutputNodes[nIndex];
		}
		else
		{
			return m_emptyNode;
		}
	}




public:
	char m_szInputFile[260];
	int m_nInputNodes;
	int m_nOutputNodes;
	
	LPSTR * m_arrayInputNodes;
	LPSTR * m_arrayOutputNodes;

	static char m_emptyNode[2];
};

char Internal_DLL_Block_RuntimeData::m_emptyNode[2] = {'\0','\0'};


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

	char szTemp[100];
	
	Internal_DLL_Block_RuntimeData * pData = (Internal_DLL_Block_RuntimeData *)(*ptrUserData);
	Internal_DLL_Block_RuntimeData * pData2 = NULL;

	switch(	nRequestReason )						
	{
		case ACTION_DLL_SELECTED: //New Element was placed on the schematic window and this DLL was selected.
			{
				switch(nRequestCode)
				{
					case REQUEST_BEGIN:
						//Allocate User data
						assert(*ptrUserData == NULL);
						*ptrUserData = new Internal_DLL_Block_RuntimeData();
						pData = (Internal_DLL_Block_RuntimeData *)(*ptrUserData);
						return;

					// in this example, parameters do not depend on input file. They are always the same.
					case REQUEST_PARAM_COUNT:
						*pnParam1 = 10; // 10 parameters
						*pnParam2 = 1; // Input Data File is required
						strcpy(szParam1, "All Files|*.*||"); //File Open Dialog Filter for InputFile.
						return;

					case REQUEST_DATAFILE_INFO:
					// Get Data File parameter information
					// char * szParam1: Label  20 characters maximum.
					// char * szParam2: Full file path   260 characters maximum.
					// int * pnParam1:  1: Show Display check box in property Dialog box    0: Do not show Display check box
						strcpy(szParam1, "Input Data File");
						*pnParam1 = 1; // Show Display check box
						return;


					case REQUEST_PARAM_INFO:
						{
							// Get parameter information
							// char * szParam1: parameter Label  20 characters maximum.
							// char * szParam2: parameter default value  50 characters maximum.
							// int * pnParam1:  1: Show Display check box     0: Do not show Display check box
							switch(nRequestParam)						
							{
								//Ten Parameters
								case 0:
									strcpy(szParam1, "Variable 1");
									strcpy(szParam2, "10000"); //Default Value
									*pnParam1 = 1; // Show Display check box
									break;

								case 1:
									strcpy(szParam1, "Variable 2");
									strcpy(szParam2, "10");//Default Value
									*pnParam1 = 1; // Show Display check box
									break;

								case 2:
									strcpy(szParam1, "Variable 3");
									strcpy(szParam2, "90");//Default Value
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 3:
									strcpy(szParam1, "Param 4");
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 4:
									strcpy(szParam1, "Param 5");
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 5:
									strcpy(szParam1, "Param 6");
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 6:
									strcpy(szParam1, "Param 7");
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 7:
									strcpy(szParam1, "Param 8");
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 8:
									strcpy(szParam1, "Param 9");
									*pnParam1 = 0; // Do not Show Display check box
									break;

								case 9:
									strcpy(szParam1, "Param 10");
									*pnParam1 = 0; // Do not Show Display check box
									break;
							}
						}
						return;


						default:
							return;
				}
			}
			return;



		case ACTION_ELEMENT_LOAD:
			{
				switch(nRequestCode)
				{
					case REQUEST_BEGIN:
						//Allocate User data
						assert(*ptrUserData == NULL);
						*ptrUserData = new Internal_DLL_Block_RuntimeData();
						pData = (Internal_DLL_Block_RuntimeData *)(*ptrUserData);

						// Copy saved data in schematic file to szTemp. in this case only the DLL version was saved
						if( *pnParam1 == 0 )
						{
							szTemp[0] = '\0';
						}
						else
						{
							memcpy(szTemp, szParam1, *pnParam1);
						}

						//Compare versions
						if( atof(MyApp_VERSION) < atof(szTemp) )
						{
							::MessageBox(NULL, "Data was saved by Newer version of \"My Program\". Please upgrade.", "My Program", MB_OK);
							//Continue loading anyway
						}
						
						if( strlen(szParam2) > 0 )
						{	//Reload input file. 
							pData->LoadFile(szParam2);
						}
						return;


					case REQUEST_IN_OUT_NODES:
						// Get the number of Input and Output nodes
						// int * pnParam1(Read, Write):  returns the number of input nodes.
						// int * pnParam2(Read, Write):  returns the number of output nodes.
						*pnParam1 = pData->m_nInputNodes;
						*pnParam2 = pData->m_nOutputNodes;
						return;


					case REQUEST_INPUT_NODE_INFO:
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get Input node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						strcpy(szParam1, pData->GetInputNodeLabel(nRequestParam));
						return;

					case REQUEST_OUTPUT_NODE_INFO:
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get Output node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						strcpy(szParam1, pData->GetOutputNodeLabel(nRequestParam));
						return;


					// in this example, parameters do not depend on input file. They are always the same.
					//  Schematic file saves and restores parameter information from last session. unless DLL version was changed 
					//     and parameter number or labels are different, there is no need to modify parameter information
					case REQUEST_PARAM_COUNT:
						return;

					case REQUEST_PARAM_INFO:
						return;


					default:
							return;
				}
			}
			return;


		case ACTION_ELEMENT_SAVE:  //Saving element to schematic file
			//		char * szParam1(Write only):  copy binary data to be saved in .SCH file(DLL version, File Version, ...) (maximum 100 bytes)
			//		int * pnParam1(Write only):   number of valid bytes in szParam1
			//		char * szParam2(Read only): Selected Input file path 
			memcpy(szParam1, MyApp_VERSION, strlen(MyApp_VERSION)+1);
			*pnParam1 = strlen(MyApp_VERSION)+1; //size of data
			return;




		case ACTION_INPUTFILE_CHANGED:
			{
				switch(nRequestCode)
				{
					case REQUEST_BEGIN:
						//		 char * szParam1(Read, Write): Selected Input file path 
						//		 int * pnParam1(Write only):  0: Reject the file    1: set to 1 or Leave unchanged to accept the file
						pData2 = new Internal_DLL_Block_RuntimeData();
						if( !(pData2->LoadFile(szParam1)) )
						{
							//Reject File.
							*pnParam1 = 0;
							delete pData2;
						}
						
						// file was good
						if( pData != NULL )
						{
							//Delete old User data and assign new one
							delete pData;
							*ptrUserData = pData = pData2;
						}
						return;


					case REQUEST_IN_OUT_NODES:
						// Get the number of Input and Output nodes
						// int * pnParam1(Read, Write):  returns the number of input nodes.
						// int * pnParam2(Read, Write):  returns the number of output nodes.
						*pnParam1 = pData->m_nInputNodes;
						*pnParam2 = pData->m_nOutputNodes;
						return;


					case REQUEST_INPUT_NODE_INFO:
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get Input node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						strcpy(szParam1, pData->GetInputNodeLabel(nRequestParam));
						return;

					case REQUEST_OUTPUT_NODE_INFO:
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get Output node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						strcpy(szParam1, pData->GetOutputNodeLabel(nRequestParam));
						return;

						default:
							return;
				}
			}
			return;



		case ACTION_ELEMENT_DELETE:
			{
				//Delete User data
				pData = (Internal_DLL_Block_RuntimeData *)(*ptrUserData);

				if( pData == NULL )
				{
					return;
				}

				delete pData;
				*ptrUserData = NULL;
			}
			return;
			

		case ACTION_PARAMETERS_CHANGED:  //parameters were changed in the property dialog box.
			{
				if( nRequestCode == REQUEST_PARAM_INFO )
				{
					//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
					// Get parameter information
					// char * szParam1: parameter Label  20 characters maximum.
					// char * szParam2: parameter default value  50 characters maximum.
					// int * pnParam1:  1: Show Display check box     0: Do not show Display check box
					switch(nRequestParam)						
					{
						//Ten Parameters
						case 0:
							//Verify Parameter value
							itoa(atoi(szParam2), szParam2, 10);//must be an integer
							break;

						case 1:
							itoa(atoi(szParam2), szParam2, 10);//must be an integer
							break;

						case 2:
							break;

						case 3:
							break;

						case 4:
							break;

						case 5:
							break;

						case 6:
							break;

						case 7:
							break;

						case 8:
							break;

						case 9:
							break;
					}
				}
			}
			return;
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

struct Internal_DLL_Block_SimulationData
{

	int m_nStepCount;
	
	int m_nInputNodes;
	int m_nOutputNodes;


	double m_fVar1;
	double m_fVar2;

	char m_szInputFile[260];

	// Add DLL Specific variables
	double m_flambda;
	double m_fL;
	
};


void OPENSIMUSER(const char *szId, const char * szNetlist, void ** ptrUserData, int *pnError, LPSTR szErrorMsg, void * pPsimParams)
{

	EXT_FUNC_PSIM_INFO * pPsimInfo = (EXT_FUNC_PSIM_INFO *)pPsimParams;


	assert(*ptrUserData == NULL);
	*ptrUserData = new Internal_DLL_Block_SimulationData;

	Internal_DLL_Block_SimulationData * pData = (Internal_DLL_Block_SimulationData *)(*ptrUserData);
	memset(pData, 0, sizeof(Internal_DLL_Block_SimulationData) );

	
	CNetListParams netlist;

	netlist.parse_netlist(szNetlist);


	assert( strcmp(netlist[0],"DLL_EXT") == 0 );
	assert( strcmp(netlist[1], szId) == 0 );


	pData->m_nInputNodes  = atoi(netlist[2]); //number of input nodes
	pData->m_nOutputNodes = atoi(netlist[3]); //number of output nodes

 	// netlist[4] : DLL FilePath

	
	int nParamStartIndex = 5 + pData->m_nInputNodes + pData->m_nOutputNodes;

	// value of parameter 1
	pData->m_fVar1 = atof( netlist[nParamStartIndex] );

	// value of parameter 2
	pData->m_fVar2 = atof( netlist[nParamStartIndex+1] );


	// Input file is always the last parameter in the netlist
	 strcpy( pData->m_szInputFile, netlist[ netlist.GetCount() - 1 ] );



	//Do DLL program specific initialization
	pData->m_flambda = 0.0;
	pData->m_fL = 0.005;



	
	*pnError = 0; //Success
}



void RUNSIMUSER(double t, double delt, double *in, double *out, void ** ptrUserData, int *pnError, LPSTR szErrorMsg)
{
	Internal_DLL_Block_SimulationData * pData = (Internal_DLL_Block_SimulationData *)(*ptrUserData);

	if( pData == NULL)
	{
		return;
	}


// Place your code here............begin
	//Assuming DLL has 1 input and 1 output ( in[0] and out[0] )

	double v, i;

	// Receive the voltage from PSIM
	v = in[0];
	
	// Integrate the voltage to obtain the flux linkage
	// value of "pData->m_flambda" and "pData->m_fL" is retained from last simulation step
	pData->m_flambda += v * delt;

	// Calculate the current
	i = pData->m_flambda / pData->m_fL;

	// Send the current back to PSIM
	out[0] = i;



// Place your code here............end

	pData->m_nStepCount++;

	*pnError = 0; //Success
}


void CLOSESIMUSER(const char *szId, void ** ptrUserData)
{
	Internal_DLL_Block_SimulationData * pData = (Internal_DLL_Block_SimulationData *)(*ptrUserData);
	assert(*ptrUserData != NULL);

	if( pData == NULL )
	{
		return;
	}

	delete pData;
	*ptrUserData = NULL;
}


