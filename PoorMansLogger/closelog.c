#include "PML.h"

BOOL WINAPI CloseLog()
{
	BOOL fReturn = FALSE;
	EnterCriticalSection(&g_CS);
	if (g_hFile != INVALID_HANDLE_VALUE)
	{
		FlushFileBuffers(g_hFile);
		CloseHandle(g_hFile);
		g_hFile = INVALID_HANDLE_VALUE;
	}
	fReturn = INVALID_HANDLE_VALUE == g_hFile;
	LeaveCriticalSection(&g_CS);
	return fReturn;
}