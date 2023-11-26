# PoorMansLogger

Simple, thread-safe, no-frills logging framework for C and C++ projects on Windows. Only supports file output at the moment.
DLL exports the following functions:

`BOOL WINAPI InitializeLog(_In_z_ WCHAR *wszFileName)` - Initialize the log file with the given filename

`BOOL WINAPI IsLogOpened()` - Returns `TRUE` if the log file is presently open; `FALSE` otherwise

`BOOL WINAPI WriteLogEntry(_In_ LOGLEVEL level, _In_z_ WCHAR *wszEntry)` - Writes a log entry `wszEntry` of the given `LOGLEVEL` value (see below). The entry has the format `"TIMESTAMP - LOGLEVEL - MESSAGE\r\n"`

`BOOL WINAPI CloseLog()` - Closes the currently open log file. Note that if the log file is not explicitly closed by the caller when the DLL is unloaded, the code in `DllMain` for `DLL_PROCESS_DETACH` will close the file when the DLL is unloaded.

`LOGLEVEL` is defined as follows:
```
typedef enum _LOGLEVEL 
{ 
	INFO = 0,
	WARNING = 1,
	FATAL = 2 
}
LOGLEVEL, *PLOGLEVEL;
```

I recommend including the file `PMLAPI.h` in any code that uses this DLL.
