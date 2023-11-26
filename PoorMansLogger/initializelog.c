#include "PML.h"

BOOL WINAPI InitializeLog(_In_z_ WCHAR *wszFileName)
{
	CONST USHORT uBOM = 0xFEFF;	DWORD dwError = ERROR_SUCCESS;
	DWORD dwWritten = 0U;
	BOOL fSuccess = FALSE;

	EnterCriticalSection(&g_CS);
	if (g_hFile != INVALID_HANDLE_VALUE)
	{
		fSuccess = FALSE;
		goto cleanup;
	}

	g_hFile = CreateFileW(wszFileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == g_hFile)
	{
		fSuccess = FALSE;
		goto cleanup;
	}

	fSuccess = TRUE;
	WriteFile(g_hFile, &uBOM, sizeof(USHORT), &dwWritten, NULL);
cleanup:
	LeaveCriticalSection(&g_CS);
	return fSuccess;
}