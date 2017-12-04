#include "StdAfx.h"
#include "TuLing.h"
/*
ͼ������� C++ʵ��

�����
����û�н��棨�ϻ����Ͼ��ǿ���̨��

����ο���΢���ṩ�����ӣ�����
https://msdn.microsoft.com/en-us/library/windows/desktop/aa384104(v=vs.85).aspx
*/

CString g_strToTuling,g_strFromTuling;

//����ת��
char *UnicodeToANSI(const wchar_t *str)
{
	static char result[1024];
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, str, -1, result, len, NULL, NULL);
	result[len] = '\0';
	return result;
}
wchar_t *UTF8ToUnicode(const char *str)
{
	static wchar_t result[1024];
	int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	MultiByteToWideChar(CP_UTF8, 0, str, -1, result, len);
	result[len] = L'\0';
	return result;
}
wchar_t *ANSIToUnicode(const char* str)
{
	int textlen;
	static wchar_t result[1024];
	textlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	memset(result, 0, sizeof(char) * (textlen + 1));
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)result, textlen);
	return result;
}

bool GetHttpPage(void)
{
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer = NULL;
	static HINTERNET hSession = WinHttpOpen(L"A Tuling API Example Program/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	static HINTERNET hConnect = NULL, hRequest = NULL;
	BOOL  bResults = FALSE;

	//�ӿ���̨����һ�����֣�ע���������������ANSI����ģ�������Ҫת���� Unicode����
	static char uin[1024]; gets_s(uin);
//	wsprintf(String, TULING_URL, ANSIToUnicode(uin));

	CString CWString;
	CWString.Format(TULING_URL,g_strToTuling);
	USES_CONVERSION; 
	LPCWSTR pwcStr = A2CW((LPCSTR)CWString); 

	//����һ��http�����ӻỰ���������������У�����������Ҳ������IP��ַ������Ҫhttp;ǰ׺
	if (hSession)
	{
		if (!hConnect)
			hConnect = WinHttpConnect(hSession, L"www.tuling123.com", INTERNET_DEFAULT_HTTP_PORT, 0);
	}

	//����һ��HTTP������
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", pwcStr, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_ESCAPE_PERCENT | WINHTTP_FLAG_REFRESH);

	//������������
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

	// �����������������
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	else
		printf("Error %d has occurred.\n", GetLastError());
	//�������ֵΪfalse������ʹ��getlasterror���õ�������Ϣ����ͬ
	//����ֵ����ϸ��Ϣ���Կ�΢����ҳ�����߿����﷭��õ����Ľӿ�˵��
	//http://blog.csdn.net/fengsh998/article/details/8201591

	// �ڲ�ʹ�õ�һ��ѭ����ȷ���ܽ��ܵ���������
	if (bResults)
	{
		do
		{
			//����Ƿ���������Ҫ����
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
			{
				printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
				break;
			}

			if (!dwSize)
				break;

			//Ϊ��������ڴ沢��ȡ
			pszOutBuffer = new char[dwSize + 1];

			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				break;
			}

			ZeroMemory(pszOutBuffer, dwSize + 1);

			if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
			{
				printf("Error %u in WinHttpReadData.\n", GetLastError());
			}
			else
			{
				//ͼ��api������������ʹ�õ���UTF-8���룬������Ҫ����ת����ANSI�����ڿ���̨��ʾ
				//printf("return:%s\n", UnicodeToANSI(UTF8ToUnicode(pszOutBuffer)) );

				//��Ϊû��ʹ��JSON�⣬�����ұ����������ַ�����
				pszOutBuffer[strlen(pszOutBuffer)-2] = '\0';
				g_strFromTuling.Format("%s",(UnicodeToANSI(UTF8ToUnicode(pszOutBuffer)) + 23));
				printf("С��:%s\n\n", UnicodeToANSI(UTF8ToUnicode(pszOutBuffer)) + 23);
				return true;
			}

			delete[] pszOutBuffer; 
			if (!dwDownloaded)
				break;

		} while (dwSize > 0);
	}

	//��β���رձ��򿪵ľ��
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return false;
}

// int main(void)
// {
// 	system("color F0");
// 	system("title �������ͼ������� ��n��");
// 	printf("\n  ����С�飬�������������! �񨌡�\n\n");
// 
// 	do{ printf("�ң�"); } while (GetHttpPage());
// 
// 	system("pause");
// 	return 0;
// }

CTuLing::CTuLing(void)
{
}


CTuLing::~CTuLing(void)
{
}

void CTuLing::LinkTuLing()
{
	GetHttpPage();
}

CString CTuLing::ChatTuling(CString myWrod)
{
	g_strToTuling.Format("%s",myWrod);
	if(GetHttpPage())
		return g_strFromTuling;
	else
		return CString("����ͼ��ʧ��");
}
