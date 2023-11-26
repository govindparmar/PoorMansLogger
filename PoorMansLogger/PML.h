#pragma once
#include <Windows.h>
#include <strsafe.h>
#include "PMLAPI.h"

#define EXTERN extern

BOOL APIENTRY DllMain(_In_ HINSTANCE hInstDLL, _In_ DWORD dwReason, _In_ LPVOID lpReserved);

EXTERN BOOL g_fLogOpened;
EXTERN HANDLE g_hFile;
EXTERN CRITICAL_SECTION g_CS;
