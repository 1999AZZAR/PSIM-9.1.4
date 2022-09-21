//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "psimblock.h"
#include "psimutil.h"
#include "blockdata.h"

#define TYPE_PORT_INPUT   0
#define TYPE_PORT_OUTPUT  1

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
	int nNode;
	
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

					case REQUEST_IN_OUT_NODES:	//Define the number of nodes
						// int * pnParam1(Read, Write):  returns the number of nodes.
						// int * pnParam2(Read, Write):  set to 0. not used for Embedded Software Block.
						*pnParam1 = 16;
						*pnParam2 = 0;
						return;


					case REQUEST_INPUT_NODE_INFO:	//Define node names
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						nNode = nRequestParam;
						switch(nNode)
						{
							case 0:
								strcpy(szParam1, "VDD/P0");
								break;

							case 1:
								strcpy(szParam1, "P1");
								break;

							case 2:
								strcpy(szParam1, "P2");
								break;

							case 3:
								strcpy(szParam1, "P3");
								break;

							case 4:
								strcpy(szParam1, "P4");
								break;

							case 5:
								strcpy(szParam1, "P5");
								break;

							case 6:
								strcpy(szParam1, "P6");
								break;

							case 7:
								strcpy(szParam1, "P7");
								break;

							case 8:
								strcpy(szParam1, "P8");
								break;

							case 9:
								strcpy(szParam1, "P9");
								break;

							case 10:
								strcpy(szParam1, "P10");
								break;

							case 11:
								strcpy(szParam1, "P11");
								break;

							case 12:
								strcpy(szParam1, "P12");
								break;

							case 13:
								strcpy(szParam1, "P13");
								break;

							case 14:
								strcpy(szParam1, "P14");
								break;

							case 15:
								strcpy(szParam1, "P15");
								break;

							default:
								//assert(0);
								break;

						}
						return;

					case REQUEST_PARAM_COUNT:	//Define number of input parameters
						*pnParam1 = 1; // 1 parameter
						*pnParam2 = 0; // Input Data File not required
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


					case REQUEST_PARAM_INFO:	//Define input parameter names
						{
							// char * szParam1: parameter Label  20 characters maximum.
							// char * szParam2: parameter default value  50 characters maximum.
							// int * pnParam1:  1: Show Display check box     0: Do not show Display check box
							switch(nRequestParam)						
							{
								//One Parameter
								case 0:
									strcpy(szParam1, "Flag for Exact Switching Calculation");
									strcpy(szParam2, "1"); //Default Value
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
						// Get the number of nodes
						// int * pnParam1(Read, Write):  returns the number of nodes.
						// int * pnParam2(Read, Write):  not used for Embedded Software Block
					//	*pnParam1 = 0;
					//	*pnParam2 = 0;
						return;


					case REQUEST_INPUT_NODE_INFO:
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get Input node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						nNode = nRequestParam;
						switch(nNode)
						{
							case 0:
							//	strcpy(szParam1, "Vm");
								break;

							case 1:
							//	strcpy(szParam1, "Vcarr");
								break;

							case 2:
							//	strcpy(szParam1, "Vgat");
								break;

							default:
								//assert(0);
								break;

						}
						return;

					case REQUEST_OUTPUT_NODE_INFO:
						//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
						//		 Get Output node information
						//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
						//strcpy(szParam1, pData->GetOutputNodeLabel(nRequestParam));
						return;


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

	int m_nNodes, m_nTmp;

	char m_szInputFile[260];

	// Add DLL Specific variables
	double Vm0, Vcarr0, Vgat0;
	int flag_exact_switching;

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


	//assert( strcmp(netlist[0],"DLL_EXT") == 0 );
	assert( strcmp(netlist[1], szId) == 0 );


	pData->m_nNodes  = atoi(netlist[2]); //number of nodes
	
	pData->m_nTmp = atoi(netlist[3]);	// netlist[3] should be 0 for Embedded Software Block
 	// netlist[4] : DLL FilePath

	
	int nParamStartIndex = 5 + pData->m_nNodes + pData->m_nTmp;

	// value of parameter 1
	pData->flag_exact_switching = atoi( netlist[nParamStartIndex] );

	// value of parameter 2
	//pData->m_fVar2 = atof( netlist[nParamStartIndex+1] );


	// Input file is always the last parameter in the netlist
	 //strcpy( pData->m_szInputFile, netlist[ netlist.GetCount() - 1 ] );


	//Initialization
	pData->Vgat0 = 0.;
	
	*pnError = 0; //Success
}


void STARTSIMUSER(int *portTypes, void ** ptrUserData, int *pnError, LPSTR szErrorMsg)
{
	Internal_DLL_Block_SimulationData * pData = (Internal_DLL_Block_SimulationData *)(*ptrUserData);
	if( pData == NULL) { return; }

	
//===========================================================
// Place your code here............begin

	for (int i=0; i<8; i++)
	{
		portTypes[i] = TYPE_PORT_INPUT; //P0-P7 are inputs
	}

	for (i=8; i<16; i++)
	{
		portTypes[i] = TYPE_PORT_OUTPUT; //P8-P15 are outputs
	}

// Place your code here............end
//=============================================================

	
	*pnError = 0; //Success
}



void RUNSIMUSER2(double t, double delt, double *ports, double *ports2, int *portTypes, void ** ptrUserData, int *pnError, LPSTR szErrorMsg)
{
	Internal_DLL_Block_SimulationData * pData = (Internal_DLL_Block_SimulationData *)(*ptrUserData);
	if( pData == NULL) { return; }

	
//===========================================================
// Place your code here............begin

	double Vm, Vcarr, Vm0, Vcarr0, Vdd;
	int iflag;


//	Inputs
	Vdd = ports[0];
	Vm = ports[1];
	Vcarr = ports[2];

	iflag = 0;		//If iflag=1, output has changed the state.

//	Implement the comparator
	if (Vm >= Vcarr)
	{
		ports[12] = 1.;
		if (pData->Vgat0 < 0.5)
			iflag = 1;
	}
	else
	{
		ports[12] = 0.;
		if (pData->Vgat0 > 0.5)
			iflag = 1;
	}

//	Calculate the exact switching instant
	if (iflag && pData->flag_exact_switching)
	{
		Vm0 = pData->Vm0;
		Vcarr0 = pData->Vcarr0;
		ports2[12] = delt*(Vm-Vcarr)/(Vm-Vm0-Vcarr+Vcarr0);
	}

	// Store the value for use in the next step
	pData->Vm0 = ports[1];
	pData->Vcarr0 = ports[2];
	pData->Vgat0 = ports[12];

// Place your code here............end
//=============================================================

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

