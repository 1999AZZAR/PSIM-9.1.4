// TestBlock3.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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


