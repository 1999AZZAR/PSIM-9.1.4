


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Request Reasons:

#define ACTION_DLL_SELECTED			0  //New Element was placed on the schematic window and this DLL was selected.

// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		char * szParam1(Read only):  full path and file name of this DLL
//		char * szParam2(Write only):  copy default file path for input data file. file must exist otherwise it will be ignored
//		Allocate memory for ptrUserData (*ptrUserData = new ...)
//		all other parameters ignored
// 
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_PARAM_COUNT, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
//		 int * pnParam2(Read, Write):  1: Data File parameter exist (only one Data File parameter is allowed)   0: no Data File parameter
//		 char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
//		 char * szParam2(Read only):  string ID associated with the element
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_DATAFILE_INFO, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Label  20 characters maximum.
//		 char * szParam2(Read, Write): if a default file name needed then set to Full file path (260 characters maximum)  otherwise leave unchanged.
//		 int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read, Write): parameter Label  20 characters maximum.
//		 char * szParam2(Read, Write): parameter default value  50 characters maximum.
//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only     
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_IN_OUT_NODES, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 Get the number of Input and Output nodes
//		 int * pnParam1(Read, Write):  returns the number of input nodes.
//		 int * pnParam2(Read, Write):  returns the number of output nodes.
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_INPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'

//		 Get Input node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_OUTPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Output node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		all other parameters ignored
//






#define ACTION_ELEMENT_LOAD			1  //Previously saved element is  being loaded from file or being pasted as part of copy/paste operation

// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		char * szParam1(Read only):  binary data that was provided by DLL at save time. (DLL version, File Version, ...)
//		int * pnParam1(Read only):   number of valid bytes in szParam1
//		char * szParam2(Read, Write): Selected Input file path if any
//		Allocate memory for ptrUserData if needed (*ptrUserData = new ...)
//
//
// 
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_PARAM_COUNT, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
//		 int * pnParam2(Read, Write):  1: Data File parameter exist (only one Data File parameter is allowed)   0: no Data File parameter
//		 char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
//		 char * szParam2(Read only):  string ID associated with the element
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_DATAFILE_INFO, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Label  20 characters maximum.
//		 char * szParam2(Read, Write): Input file path (260 characters maximum).
//		 int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read, Write): parameter Label  20 characters maximum.
//		 char * szParam2(Read, Write): parameter default value  50 characters maximum.
//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_IN_OUT_NODES, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 Get the number of Input and Output nodes
//		 int * pnParam1(Read, Write):  returns the number of input nodes.
//		 int * pnParam2(Read, Write):  returns the number of output nodes.
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_INPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Input node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_OUTPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Output node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//





#define ACTION_ELEMENT_SAVE			2  //Saving element to file or to buffer(Copy/paste operation)

// REQUESTUSERDATA(ACTION_ELEMENT_SAVE, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		char * szParam1(Write only):  copy binary data to be saved in .SCH file(DLL version, File Version, ...) (maximum 100 bytes)
//		int * pnParam1(Write only):   number of valid bytes in szParam1
//		char * szParam2(Read only): Selected Input file path 
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_SAVE, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 




#define ACTION_INPUTFILE_CHANGED	3  //a new input file was selected

// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Selected Input file path 
//		 int * pnParam1(Write only):  0: Reject the file    1: set to 1 or Leave unchanged to accept the file
//
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_PARAM_COUNT, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
//		 int * pnParam2(Read, Write):  1: Data File parameter exist (only one Data File parameter is allowed)   0: no Data File parameter
//		 char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
//		 char * szParam2(Read only):  string ID associated with the element
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_DATAFILE_INFO, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Label  20 characters maximum.
//		 char * szParam2(Read, Write): Input file path (260 characters maximum).
//		 int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read, Write): parameter Label  20 characters maximum.
//		 char * szParam2(Read, Write): parameter default value  50 characters maximum.
//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_IN_OUT_NODES, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 Get the number of Input and Output nodes
//		 int * pnParam1(Read, Write):  returns the number of input nodes.
//		 int * pnParam2(Read, Write):  returns the number of output nodes.
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_INPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Input node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_OUTPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Output node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//







#define ACTION_PARAMETERS_CHANGED	4  //parameters were changed in the property dialog box.
//       you may Modify parameters and update user data based on new parameters 
// REQUESTUSERDATA(ACTION_PARAMETERS_CHANGED, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//
//
//
// REQUESTUSERDATA(ACTION_PARAMETERS_CHANGED, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read Only): parameter Label.
//		 char * szParam2(Read, Write): parameter value.
//
//
//
// REQUESTUSERDATA(ACTION_PARAMETERS_CHANGED, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//





#define ACTION_ELEMENT_DELETE	5  //element is being deleted or file is being closed

// REQUESTUSERDATA(ACTION_ELEMENT_DELETE, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		Delete alocated memory for ptrUserData ( delete *ptrUserData; )
//
// REQUESTUSERDATA(ACTION_ELEMENT_DELETE, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Request Codes:


// 
#define REQUEST_BEGIN	10	
	// all values depend on "int nRequestReason"  value

#define REQUEST_END		11	
	// all values depend on "int nRequestReason"  value


// Get the number of Input and Output nodes
#define REQUEST_IN_OUT_NODES	1	
	// int * pnParam1(Read, Write):  returns the number of input nodes.
	// int * pnParam2(Read, Write):  returns the number of output nodes.
	//nRequestParam, szParam1, szParam2 : ignored



// Get the number of parameters
#define REQUEST_PARAM_COUNT		2   
	// int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
	// int * pnParam2(Read, Write):  1: Data File parameter exist (only one Data File parameter is allowed)   0: no Data File parameter
	// char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
	// char * szParam2(Read only):  string ID associated with the element
	//nRequestParam :ignored


// Get Input node information
#define REQUEST_INPUT_NODE_INFO	3
	//int nRequestParam : Zero based node index (node1: 0,  node2: 1,  node3: 2, ...)
	// char * szParam1(Read, Write): Node Label  20 characters maximum.
	//pnParam1, pnParam2, szParam2 : ignored



// Get Output node information
#define REQUEST_OUTPUT_NODE_INFO 4  
	//int nRequestParam : Zero based node index (node1: 0,  node2: 1,  node3: 2, ...)
	// char * szParam1(Read, Write): Node Label  20 characters maximum.
	//pnParam1, pnParam2, szParam2 : ignored



// Get Data File information
#define REQUEST_DATAFILE_INFO	5 
	// char * szParam1(Read, Write): Label  20 characters maximum.
	// char * szParam2(Read Only): Full path and file name of Selected file.
	// int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
	//nRequestParam, szParam2, pnParam2 : ignored



// Get parameter information
#define REQUEST_PARAM_INFO 6  
	//int nRequestParam(Read only) : Zero based parameter index (parameter1: 0,   parameter2: 1,    parameter3: 2, ...)
	// char * szParam1(Read, Write): Label,  20 characters maximum.
	// char * szParam2(Read, Write): value,  50 characters maximum.
	//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only
	//pnParam2 : ignored




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DLLBLOCK_OPTION_DISPLAY_CHECKBOX		0X00000001
#define DLLBLOCK_OPTION_READ_ONLY				0X00000002


