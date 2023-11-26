#include "PML.h"

BOOL WINAPI WriteLogEntry(_In_ LOGLEVEL level, _In_z_ WCHAR *wszEntry)
{
	DWORD dwWritten = 0U;
	CONST WCHAR wCRLF[2U] = { '\r', '\n' };
	WCHAR wszTimeString[80U];
	SYSTEMTIME st;
	HRESULT hr;
	UINT uLen;
	BOOL fWrite = FALSE;

	if (!IsLogOpened() || (level != INFO && level != WARNING && level != FATAL))
	{
		return FALSE;
	}

	GetLocalTime(&st);
	StringCchPrintfW(wszTimeString, 80U, L"%.4hu-%.2hu-%.2hu %.2hu:%.2hu:%.2hu ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	
	hr = StringCbLengthW(wszTimeString, 80U * sizeof(WCHAR), &uLen);
	if (FAILED(hr))
	{
		return FALSE;
	}
	//WriteFile(g_hFile, wszTimeString)
	EnterCriticalSection(&g_CS);
	WriteFile(g_hFile, wszTimeString, uLen, &dwWritten, NULL);
	switch (level)
	{
	case WARNING:
		fWrite = WriteFile(g_hFile, L"WARNING: ", 9U * sizeof(WCHAR), &dwWritten, NULL);
		break;
	case FATAL:
		fWrite = WriteFile(g_hFile, L"FATAL: ", 7U * sizeof(WCHAR), &dwWritten, NULL);
		break;
	case INFO:
	default:
		fWrite = WriteFile(g_hFile, L"INFO: ", 6U * sizeof(WCHAR), &dwWritten, NULL);
		break;
	}

	if (!fWrite)
	{
		goto cleanup;
	}
	fWrite = FALSE;
	hr = StringCbLengthW(wszEntry, 5000U * sizeof(WCHAR), &uLen);
	if (SUCCEEDED(hr))
	{
		WriteFile(g_hFile, wszEntry, uLen, &dwWritten, NULL);
		WriteFile(g_hFile, wCRLF, sizeof(wCRLF), &dwWritten, NULL);
		fWrite = TRUE;
	}
cleanup:
	LeaveCriticalSection(&g_CS);
	return fWrite;
}
