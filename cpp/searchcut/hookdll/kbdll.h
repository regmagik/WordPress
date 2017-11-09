
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KBDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KBDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef KBDLL_EXPORTS
#define KBDLL_API __declspec(dllexport)
#else
#define KBDLL_API __declspec(dllimport)
#endif

typedef KBDLL_API void SAVE_HOOK_FN(HHOOK ThisHook);

typedef KBDLL_API BOOL RepeatLastSearchAvailableFn();
typedef KBDLL_API BOOL SearchFromClipboardAvailableFn();

typedef KBDLL_API void RepeatLastSearchFn();

typedef KBDLL_API void SearchFromClipboardFn();

