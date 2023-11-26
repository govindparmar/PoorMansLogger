#include "PML.h"

BOOL WINAPI IsLogOpened()
{
	BOOL fLogOpened = FALSE;
	EnterCriticalSection(&g_CS);
	fLogOpened = g_fLogOpened;
	LeaveCriticalSection(&g_CS);
	return fLogOpened;
}