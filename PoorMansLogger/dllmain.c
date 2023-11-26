#include "PML.h"

BOOL g_fLogOpened;
HANDLE g_hFile;
CRITICAL_SECTION g_CS;

BOOL APIENTRY DllMain(_In_ HINSTANCE hInstDLL, _In_ DWORD dwReason, _In_ LPVOID lpReserved)
{
	if (DLL_PROCESS_ATTACH == dwReason)
	{
		g_fLogOpened = FALSE;
		g_hFile = INVALID_HANDLE_VALUE;
		if (!InitializeCriticalSectionAndSpinCount(&g_CS, 0x00000400U))
		{
			return FALSE;
		}
	}
	if (DLL_PROCESS_DETACH == dwReason)
	{
		if (g_hFile != INVALID_HANDLE_VALUE)
		{
			FlushFileBuffers(g_hFile);
			CloseHandle(g_hFile);
			g_hFile = INVALID_HANDLE_VALUE;
		}
		DeleteCriticalSection(&g_CS);
	}

	return TRUE;
}