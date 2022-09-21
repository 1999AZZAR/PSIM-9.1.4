


#define REQUEST_NODE_INFO			1
#define REQUEST_COEFF_A				2
#define REQUEST_PREV				3
#define REQUEST_COEFF_B				4
#define REQUEST_STATE_UPDATE		5
#define REQUEST_STATE_READ			6
#define REQUEST_STATE_WRITE			7
#define REQUEST_CONVERGENCE			8
#define REQUEST_DLL_OUTPUT			9


#define FLAG_BACKWARD_EULER 1
#define FLAG_TRAPEZOIDAL	2

#pragma pack(push,BlockData_Enter)
#pragma pack(1)


struct DllDeviceData
{
	void * m_pUserData;

	int m_nRequestCode;
	int m_nRequestFlag;				//FLAG_BACKWARD_EULER or FLAG_TRAPEZOIDAL
	int m_nRequestNodeIndex;		//Current node number (1 based index)

	double m_fT;
	double m_fDeltaT;

	int m_nExtLinearNodes;			//No. of external linear node 
	int m_nExtQuasiNonLinearNodes;	//No. of external quasi-nonlinear node
	int m_nExtNonLinearNodes;		//No. of external nonlinear node

	int m_nIntLinearNodes;			//No. of internal linear node
	int m_nIntQuasiNonLinearNodes;	//No. of internal quasi-nonlinear node
	int m_nIntNonLinearNodes;		//No. of internal nonlinear node

	int m_nMechShaftLinear;			//No. of mechanical shafts with linear mech. equations
	int m_nMechShaftQuasiNonLinear;	//No. of mechanical shafts with quasi-nonlinear mech. equations
	int m_nMechShaftNonLinear;		//No. of mechanical shafts with nonlinear mech. equations

	int m_nSignalInNodes;			//No. of signals going into DLL
	int m_nSignalOutNodes;			//No. of signals coming out of DLL

	int m_nIntStates;				//No. of internal state variables
	int m_nOutputDisplay;			//No. of output display

	int m_nNonlinearFlag;			//Flag for RHS nonlinearity (0: linear; 1: nonlinear)
	int m_nConvergenceFlag;			//Flag for convergence of nonlinear elements (0: solution converged; 1: solution not converged)

	int * m_pMechShaftFlags;		//Mech. Shaft flags

	int m_nVoltagesSize;
	double * m_pfVoltages;			//Voltage Array

	int m_nCoeff_ASize;
	double * m_pfCoeff_A;			//Coeff. A Array

	int m_nCoeff_BSize;
	double * m_pfCoeff_B;			//Coeff. B Array

	int m_nStateVariablesSize;
	double * m_pfStateVariables;	//Internal State Variable Array

	int m_nSignalInSize;
	double * m_pfSignalIn;			//Signal In Array

	int m_nSignalOutSize;
	double * m_pfSignalOut;			//Signal Out Array

	int m_nOutputDisplaySize;
	double * m_pfOutputDisplay;		//Output Display Array

#define LEN_OUTPUT_DISPLAY_NAME		500
	char m_szOutputDisplayName[LEN_OUTPUT_DISPLAY_NAME];



	DllDeviceData() 
	{ 
		memset(this, 0, sizeof(DllDeviceData));
		//m_pIntegerArray = new int[DDD_INT_ARRAY_SIZE];

	}

	~DllDeviceData()
	{
		if( m_pMechShaftFlags != NULL )
		{
			delete m_pMechShaftFlags;
		}
		if( m_pfVoltages != NULL )
		{
			delete m_pfVoltages;
		}
		if( m_pfCoeff_A != NULL )
		{
			delete m_pfCoeff_A;
		}
		if( m_pfCoeff_B != NULL )
		{
			delete m_pfCoeff_B;
		}
		if( m_pfStateVariables != NULL )
		{
			delete m_pfStateVariables;
		}
		if( m_pfSignalIn != NULL )
		{
			delete m_pfSignalIn;
		}
		if( m_pfSignalOut != NULL )
		{
			delete m_pfSignalOut;
		}
		if( m_pfOutputDisplay != NULL )
		{
			delete m_pfOutputDisplay;
		}
	}
};



struct EXT_FUNC_PSIM_INFO
{
	char m_szPsimDir[260];
	char m_szSchDir[260];
	char m_szSchFileName[260];

	int  m_bLoadFlag;
};


#pragma pack(pop,BlockData_Enter)


