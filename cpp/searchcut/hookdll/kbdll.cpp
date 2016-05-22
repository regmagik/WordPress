// kbdll.cpp : Defines the entry point for the DLL application.
#pragma comment(linker, "/OPT:NOWIN98")

#include "stdafx.h"
#include "kbdll.h"
#include "tchar.h"
#include "stdio.h"
#include "stdlib.h"
#include "Shellapi.h"
#include "Shlwapi.h" // PathAppend
#include "Shlobj.h" // SHGetSpecialFolderPath

//#define MAX_EMAIL 260

// Includes search url and parameters.
#define MAX_REQUEST 512

//TCHAR szName[MAX_EMAIL];
//TCHAR szAddress[MAX_EMAIL];

TCHAR szPath[MAX_PATH] = TEXT("");
/*
extern "C"
KBDLL_API LPCTSTR GetOutputFileName()
{
	if(!*szPath)
	{
//		if(!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL|CSIDL_FLAG_CREATE, NULL, 0, szPath))) 
		if(!SUCCEEDED(SHGetSpecialFolderPath(NULL, szPath, CSIDL_PERSONAL, TRUE))) 
		{
			lstrcpy(szPath, TEXT("C:\\"));//TODO: need to get smarter if the call above fails
		}
		PathAppend(szPath, TEXT("Searchcut.log.txt"));
	}
	return szPath;
}

#define MAX_BUFFER 1024 
void Output(LPCTSTR pszFormat, ...)
{
	static TCHAR string[MAX_BUFFER];

	HANDLE hFile = CreateFile(GetOutputFileName(), FILE_APPEND_DATA,
						   FILE_SHARE_READ|FILE_SHARE_WRITE,    // Enables subsequent open operations on a file or device to request write access.
						   NULL,                // default security
						   OPEN_ALWAYS,          // Creates a new file, only if it does not already exist.
						   FILE_ATTRIBUTE_NORMAL,  // normal file
						   NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		return;
	}
	int limit = MAX_BUFFER - 2; //account for end of line
	if(lstrlen(pszFormat) < limit)
	{
		va_list vl;
		va_start(vl, pszFormat);
		int size = wvsprintf(string, pszFormat, vl);
		va_end(vl);

		if(size > limit)
			size = limit;
		string[size] = '\0';
		lstrcat(string, TEXT("\r\n"));
	}
	else
	{
		for(int i=0; i<limit; i++)
			string[i] = pszFormat[i];
		string[limit] = 0;
	}
    DWORD dwResult;
    if(!WriteFile (hFile, string, lstrlen(string)*sizeof(TCHAR), &dwResult, NULL))
    {
        //printf("Could not write to file (error %d)\n", GetLastError());
        //return;
    }
	::CloseHandle(hFile);
	// to debug
#ifdef _DEBUG
	OutputDebugString(string);
#endif
}
*/
void ShellExecuteOrReportError(LPCTSTR verb, LPCTSTR szURL)
{
//	Output(TEXT("%s: %s"), verb ? verb : TEXT(""), szURL);
	HINSTANCE shellExecute = ShellExecute(NULL, verb, (szURL), NULL, NULL, SW_SHOWNORMAL);
	if((int)shellExecute > 32) return; // no error

//	Output(TEXT("Shell operation %s failed (error code:%d) for %s"), verb ? verb : TEXT(""), shellExecute, szURL);
}

#define OpenWebPage(szURL) ShellExecuteOrReportError(TEXT("open"), (szURL));

#pragma data_seg(".shared") 
HHOOK g_ThisHook = NULL;
DWORD dwTick = 0;
#pragma data_seg() 

TCHAR szRequest[MAX_REQUEST];
TCHAR szLastRequest[MAX_REQUEST];

#pragma comment(linker, "/SECTION:.shared,RWS") 
//LPCTSTR SearchUrl = _T("http://www.google.com/cse?cx=partner-pub-0252080858300003:7317513899&q=");
LPCTSTR SearchUrl = _T("http://google.com/search?ie=utf8&q=");

extern "C"
KBDLL_API void RepeatLastSearch()
{
	OpenWebPage(szLastRequest)
}

extern "C"
KBDLL_API BOOL RepeatLastSearchAvailable()
{
	return *szLastRequest;
}

void ProcessString(int charCount)
{	
//	TCHAR szRequestFormat[] = "http://google.com/search?q=%s";
//	TCHAR szRequestFormat[] = "http://www.google.com/cse?cx=partner-pub-0252080858300003:7317513899&q=%s";
	int n1 = lstrlen(SearchUrl);
	if(n1 > MAX_REQUEST)return;

	//First, get string from szRequest and convert it to UTF8
	char utf8[MAX_REQUEST];
	::WideCharToMultiByte(CP_UTF8, 0, szRequest, charCount, utf8, MAX_REQUEST, NULL, NULL); 
						//MessageBoxA(NULL, utf8, "WideCharToMultiByte", MB_OK);// displays garbage for cyrillic, but actual values are correct.
	
	lstrcpy(szRequest, SearchUrl);

	for(LPCSTR p = utf8; *p; p++)
	{
		if(n1 + 4 > MAX_REQUEST) break;

		// unreserved symbols - as is
		if(*p > 'a' && *p < 'z' || *p > 'A' && *p < 'Z' || *p > '0' && *p < '9' || *p == '-' || *p == '_' || *p == '.' || *p == '~') szRequest[n1++] = *p;
		else if (*p == ' ') szRequest[n1++] = '+';
		else
		{
			szRequest[n1++] = '%';
			char utf8Byte[13];
			sprintf(utf8Byte,"%02X", *p & 0xFF); 
			szRequest[n1++] = utf8Byte[0];
			szRequest[n1++] = utf8Byte[1];
		}
	}
	szRequest[n1] = 0;

	OpenWebPage(szRequest)
	lstrcpy(szLastRequest, szRequest);
}
/*
void ProcessSerialNum(TCHAR *str)
{
	if(!*szAddress)
		return;
	TCHAR szRequest[MAX_REQUEST];
	sprintf(szRequest, "http://regmagik.com/RegUser/AddSerialNumber.aspx?SerialNumber=%s&UserName=%s&UserEmail=%s", str, szName, szAddress);
	OpenWebPage(szRequest)

		// clear user info
	*szName = 0;
	*szAddress = 0;
}

bool IsEmail(TCHAR *str)
{
	// assume email is given as Name <address>
	TCHAR *lt = _tcschr(str, '<');
	if(!lt)
		return false;
	TCHAR *gt = _tcschr(str, '>');
	if(!gt)
		return false;
	TCHAR *at = _tcschr(lt, '@');
	if(!at)
		return false;

	int len = lt-str;
	if(len >= MAX_EMAIL)
		len = MAX_EMAIL - 1;
	strncpy(szName, str, len);
	szName[len] = 0;
	// TRIM RIGHT SPACES
	while(len--)
	{
		if(!_istspace(szName[len]))
			break;
		szName[len] = 0;
	}

	len = gt-lt-1;
	if(len >= MAX_EMAIL)
		len = MAX_EMAIL - 1;
	strncpy(szAddress, lt+1, len);
	szAddress[len] = 0;
	// TRIM RIGHT SPACES
	while(len--)
	{
		if(!_istspace(szAddress[len]))
			break;
		szAddress[len] = 0;
	}

	sprintf(szRequest, "http://regmagik.com/RegUser/CheckNewUser.aspx?UserEmail=%s", szAddress);
//	sprintf(szRequest, "http://regmagik.com/RegUser/AddUser.aspx?UserName=%s&UserEmail=%s", szName, szAddress);
	OpenWebPage(szRequest)
	return true;
}

void OnCtrlInsIns()
{
//	Output(TEXT("CtrlInsIns detected."));
	if(IsClipboardFormatAvailable(CF_UNICODETEXT))
	{
        if(::OpenClipboard(NULL))
		{
			HGLOBAL hglb=GetClipboardData(CF_UNICODETEXT); 
			if(hglb) 
			{ 
				SIZE_T nSize = GlobalSize(hglb) / sizeof(TCHAR);
				if(nSize > 300)	nSize = 300;	// we don't need long text here
				LPCTSTR pClipboardText=(LPCTSTR)GlobalLock(hglb); 
				if(pClipboardText) 
				{
//					LPTSTR str = new TCHAR[nSize+1];
//					if(str)
					{
//						memcpy(str, pClipboardText, nSize);
//						str[nSize] = '\0';

						//MessageBox(NULL, pClipboardText, _T("From Clipboard"), MB_OK);
						ProcessString(pClipboardText, nSize);

//						if(!IsEmail(str))
//						{
//							// must be serial number
//							ProcessSerialNum(str);
//						}

//						delete str;
					}
					GlobalUnlock(hglb); 
				}
			} 
			CloseClipboard(); 
		}
	}
}
*/
//Copy text from clipboard to buffer and return number of chars copied
UINT GetClipboardText()
{
    if (!OpenClipboard(NULL)) return 0;
	void *hglb = GetClipboardData(CF_UNICODETEXT); 
	LPTSTR lpstr = (LPTSTR)GlobalLock(hglb); 
	DWORD size = ::GlobalSize(hglb);

	//TODO: skip non-searcheable sequences, like =====

	// copy up to MAX symbols
//	int len = lstrlen(lpstr);
	int len = size/sizeof(TCHAR);
	if(size) //
	{
		if(len >= MAX_REQUEST) len = MAX_REQUEST - 1;
		memcpy(szRequest, lpstr, size); 
//		memcpy(szRequest, lpstr, len * sizeof(TCHAR)); 
//		lstrcpyn(szRequest, lpstr, len); 
		szRequest[len] = 0;
	}

	GlobalUnlock(hglb); 
	CloseClipboard();
	return len;// Return false if the clipboard was empty.
}

void OnCtrlInsIns()
{
//	MessageBoxA(NULL, "OnCtrlInsIns", "OnCtrlInsIns", MB_OK);// displays garbage for cyrillic, but actual values are correct.
	UINT count = GetClipboardText();
	if(count) ProcessString(count);

}

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

extern "C"
KBDLL_API void SaveThisHook(HHOOK ThisHook) 
{
//	MessageBoxA(NULL, ThisHook?"Got ThisHook":"No ThisHook", "SaveThisHook", MB_OK);
	//if(!g_ThisHook) 
	g_ThisHook = ThisHook;
	*szLastRequest = 0;
}

#define KEY_WAS_DOWN_BIT (1 << 30)		// 1 - the key was previously down
#define KEY_UP_BIT (1 << 31)				// 1 - the key is being released
 
//WH_KEYBOARD hook procedure  
extern "C"
KBDLL_API LRESULT KbdPrc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
    if (nCode == HC_ACTION)
	{
		SHORT bControl = 0X8000 & GetKeyState(VK_CONTROL);	// if control was pressed
		bool bInsert = wParam == VK_INSERT || wParam == 0x43;
		if(bControl && bInsert)
		{
//			MessageBoxA(NULL, "bControl && bInsert", "KbdPrc", MB_OK);
			bool bKeyUp = (lParam & KEY_WAS_DOWN_BIT) && (lParam & KEY_UP_BIT);
			if(bKeyUp)
			{
				if(dwTick && GetTickCount() - dwTick < 400)
				{
					dwTick = 0;
					OnCtrlInsIns();
				}
				else
				{
					dwTick = GetTickCount();
				}
			}
		}
	}
    return CallNextHookEx(g_ThisHook, nCode, wParam, lParam); 
} 


extern "C"
KBDLL_API void SearchFromClipboard()
{
	ProcessString(GetClipboardText());
}

extern "C"
KBDLL_API BOOL SearchFromClipboardAvailable()
{
	return GetClipboardText();
}

