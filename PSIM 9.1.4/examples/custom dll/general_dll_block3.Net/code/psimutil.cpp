
#include "StdAfx.h"
#include "psimutil.h"




CNetListParams::CNetListParams() 
{
	m_strParams = NULL;
	m_nNumParams = 0;

}

CNetListParams::~CNetListParams() 
{
	Clear();
}

void CNetListParams::Clear()
{
	int nCtr;
	for(nCtr=0; nCtr<m_nNumParams; nCtr++)
	{
		if( m_strParams[nCtr] != NULL )
		{
			delete [] m_strParams[nCtr];
		}
		m_strParams[nCtr] = NULL;
	}
	if( m_strParams != NULL )
	{
		delete [] m_strParams;
	}
	m_strParams = NULL;
	m_nNumParams = 0;
}



int CNetListParams::parse_netlist(LPCSTR strInput)
{
	int nMaxParams = 10;

	m_strParams = new LPSTR[nMaxParams];
	memset(m_strParams, 0, sizeof(LPCSTR*) * nMaxParams);
	m_nNumParams = 0;

	char ch;
	int nBufferLen = 100;
	char * buffer = new char[nBufferLen];
	
	BOOL bEndLoop = FALSE;
	BOOL bSaveField = FALSE;
	int nIndex = 0;
	int nCtr = 0;
	BOOL bQuot = FALSE;

	while (!bEndLoop)
	{
		ch = strInput[nIndex];
		nIndex++;
		if( (ch == '\0') || (ch == '\r') || (ch == '\n') )
		{
			bEndLoop = TRUE;
			if( nCtr !=0 )
			{
				bSaveField = TRUE;
			}
		}
		else if( !bQuot && (ch == ' ') || (ch == '\t') )
		{
			bSaveField = TRUE;
		}
		else if( (ch == '\"') && (nCtr == 0) && !bQuot )
		{
			bQuot = TRUE;
		}
		else if( (ch == '\"') && bQuot )
		{
			bQuot = FALSE;
			bSaveField = TRUE;
		}
		else
		{
			buffer[nCtr] = ch;
			nCtr++;
			if( nCtr >= nBufferLen-10 )
			{
				nBufferLen += 100;
				char * buffer2 = new char[nBufferLen];
				memcpy(buffer2, buffer, nCtr+2);
				delete [] buffer;
				buffer = buffer2;
			}
		}
		
		if (bSaveField)
		{
			buffer[nCtr] = '\0';

			if( (m_nNumParams+1) >= nMaxParams )
			{
				nMaxParams += 10;

				LPSTR * strParamsTemp = new LPSTR[nMaxParams];
				memcpy(strParamsTemp, m_strParams, sizeof(LPCSTR*) * m_nNumParams);
				memset(strParamsTemp + m_nNumParams, 0, sizeof(LPCSTR*) * (nMaxParams - m_nNumParams));
				delete m_strParams;
				m_strParams = strParamsTemp;
			}
			m_strParams[m_nNumParams] = new char[nCtr+2];
			strcpy(m_strParams[m_nNumParams], buffer);
			m_nNumParams++;

			nCtr = 0;
			bSaveField = FALSE;
		}
	}
	delete [] buffer;
	return TRUE;
}

