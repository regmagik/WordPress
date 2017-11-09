// Pimp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "..\hookdll\kbdll.h"

#include "SystemTraySDK.h"
CSystemTray TrayIcon;

TCHAR szExePath[MAX_PATH];
TCHAR szFindTarget[MAX_PATH];

#define FindTarget() ShellExecute(NULL, _T("Open"), _T("Explorer"), szFindTarget, NULL, SW_SHOWNORMAL);

void OpenWebsite()
{
	ShellExecute(NULL, _T("open"), _T("http://www.regmagik.com/searchcut/"), NULL, NULL, SW_NORMAL);
}

void AutoStart()
{
	HKEY hRun;
	HRESULT hr = ::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &hRun); 
	if(FAILED(hr)) return;
	hr = ::RegSetValueEx(hRun, _T("Searchcut"), 0, REG_SZ, (BYTE*)szExePath, (lstrlen(szExePath)+1)*sizeof(TCHAR));
}

void MinimizeWindow(HWND hWnd)
{
    TrayIcon.MinimiseToTray(hWnd);
}

#define	WM_ICON_NOTIFY WM_APP+10

#pragma comment(linker, "/OPT:NOWIN98")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
TCHAR szHello[MAX_LOADSTRING];

RepeatLastSearchAvailableFn *pRepeatLastSearchAvailableFn = NULL;
RepeatLastSearchFn *pRepeatLastSearchFn = NULL;

SearchFromClipboardAvailableFn *pSearchFromClipboardAvailableFn = NULL;
SearchFromClipboardFn *pSearchFromClipboardFn = NULL;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	int exitCode = 0;
	HINSTANCE hDLL = NULL;
	SAVE_HOOK_FN *fp = NULL;
	HOOKPROC hkKbdPrc = NULL;
	HHOOK hKbdHook = NULL;
	
	HANDLE hMutex = CreateMutex(NULL,	// default security descriptor
								FALSE,	// mutex not owned
        TEXT("Local\\GuznerSearchUtilityMutexToEnforceSingleApplicationInstancePerSession"));

    if (hMutex != NULL && GetLastError() == ERROR_ALREADY_EXISTS) goto exit;

	::GetModuleFileName(hInstance, szExePath, MAX_PATH);

	// prepare find target command 
	lstrcpy(szFindTarget, _T("/n,/select,\"")); lstrcat(szFindTarget, szExePath); lstrcat(szFindTarget, _T("\"")); 

#ifdef _DEBUG
	hDLL = LoadLibrary(_T("Debug.kbdll.dll"));
#else
	hDLL = LoadLibrary(_T("kbdll.dll"));
#endif
	if(hDLL) 
	{

		pRepeatLastSearchAvailableFn = (RepeatLastSearchAvailableFn*)GetProcAddress(hDLL, "RepeatLastSearchAvailable");
		pRepeatLastSearchFn = (RepeatLastSearchFn*)GetProcAddress(hDLL, "RepeatLastSearch");

		pSearchFromClipboardAvailableFn = (SearchFromClipboardAvailableFn*)GetProcAddress(hDLL, "SearchFromClipboardAvailable");
		pSearchFromClipboardFn = (SearchFromClipboardFn*)GetProcAddress(hDLL, "SearchFromClipboard");

		if((fp = (SAVE_HOOK_FN*)GetProcAddress(hDLL, "SaveThisHook")) != NULL 
			&& (hkKbdPrc = (HOOKPROC)GetProcAddress(hDLL, "KbdPrc")) != NULL)
		{
			hKbdHook = SetWindowsHookEx(WH_KEYBOARD,hkKbdPrc,hDLL,0); 
			(fp)(hKbdHook);
		}
	}

	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_WINDOW_CLASS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
		goto exit;

	// message loop
	{
		HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)ID_MAIN); 

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0)) 
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		exitCode = msg.wParam;
	}
exit:
//	if(fp)(fp)(NULL);
	if(hKbdHook)UnhookWindowsHookEx(hKbdHook);
	if(hDLL)FreeLibrary(hDLL);
	if(hMutex)CloseHandle(hMutex);

	return exitCode;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PIMP);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)ID_MAIN;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

	// Create the tray icon
	if (!TrayIcon.Create(hInstance, hWnd, // Parent window
                         WM_ICON_NOTIFY, // Icon notify message to use
                         szHello,  // tooltip
                         ::LoadIcon(hInstance, (LPCTSTR)IDI_SMALL),
                         IDM_TRAY)) 
        return FALSE;

//	TrayIcon.ShowBaloon(szHello, szTitle, NIIF_INFO, 15);

//   ShowWindow(hWnd, nCmdShow);
//   ShowWindow(hWnd, SW_MINIMIZE);
//   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	PAINTSTRUCT ps;
	HDC hdc;
	HMENU menu = NULL;

	switch (message) 
	{
//		case WM_CREATE:
//			break;
        case WM_ICON_NOTIFY:
            return TrayIcon.OnTrayNotification(wParam, lParam);

		case WM_INITMENUPOPUP:
			menu = (HMENU)wParam;
			::EnableMenuItem(menu, ID_REPEAT_LAST, 
				(pRepeatLastSearchAvailableFn && (pRepeatLastSearchAvailableFn)()) ? MF_ENABLED : MF_GRAYED);
			::EnableMenuItem(menu, ID_CLIPBOARD, 
				pSearchFromClipboardAvailableFn && pSearchFromClipboardAvailableFn() ? MF_ENABLED : MF_GRAYED);
            break; 

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case ID_START_AUTOMATICALLY:
					AutoStart();
				   break;
				case ID_WINDOWS_EXPLORER:
					FindTarget()
				   break;
				case ID_CLIPBOARD:
					pSearchFromClipboardFn();
				   break;
				case ID_REPEAT_LAST:
					if(pRepeatLastSearchAvailableFn && pRepeatLastSearchAvailableFn() && pRepeatLastSearchFn) 
						pRepeatLastSearchFn();
				   break;
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case ID_ONLINE:
					OpenWebsite();
				   break;
				case ID_OPEN:
					TrayIcon.MaximiseFromTray(hWnd);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_SYSCOMMAND:
			switch (wParam)
            {
				case SC_MINIMIZE:
				   MinimizeWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
            }
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, lstrlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_CLOSE:
            PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDOK :
			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			case ID_WEB:
				OpenWebsite();
				return TRUE;
			}
	}
    return FALSE;
}
