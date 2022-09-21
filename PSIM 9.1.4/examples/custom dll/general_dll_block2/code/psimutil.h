
#ifndef H_PSIMUTIL_987UCNVIUH49NVJHN8U4UV4WNG89GHB_HEADER
#define H_PSIMUTIL_987UCNVIUH49NVJHN8U4UV4WNG89GHB_HEADER



struct EXT_FUNC_PSIM_INFO
{
	char m_szPsimDir[260];
	char m_szSchDir[260];
	char m_szSchFileName[260];
};


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


