#pragma once
#include <Windows.h>
#include <strsafe.h>

typedef enum _LOGLEVEL 
{ 
	INFO = 0,
	WARNING = 1,
	FATAL = 2 
}
LOGLEVEL, *PLOGLEVEL;

BOOL WINAPI IsLogOpened();
BOOL WINAPI InitializeLog(_In_z_ WCHAR *wszFileName);
BOOL WINAPI CloseLog();
BOOL WINAPI WriteLogEntry(_In_ LOGLEVEL level, _In_z_ WCHAR *wszEntry);
