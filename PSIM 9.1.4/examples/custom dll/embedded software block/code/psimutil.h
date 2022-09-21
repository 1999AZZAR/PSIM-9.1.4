
#ifndef H_PSIMUTIL_987UCNVIUH49NVJHN8U4UV4WNG89GHB_HEADER
#define H_PSIMUTIL_987UCNVIUH49NVJHN8U4UV4WNG89GHB_HEADER



class CNetListParams
{
public:
	LPSTR * m_strParams;
	int m_nNumParams;


	CNetListParams();

	~CNetListParams();

	void Clear();

	int parse_netlist(LPCSTR strInput);


	int GetCount() { return m_nNumParams; }
	char * GetAt(int nIndex) { return m_strParams[nIndex]; }
	char * operator [] (int nIndex) { return m_strParams[nIndex]; }

};


#endif  //H_PSIMUTIL_987UCNVIUH49NVJHN8U4UV4WNG89GHB_HEADER


