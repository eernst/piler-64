#include "piler2.h"

#if	WIN32
#include <windows.h>
#include <psapi.h>

double GetRAMSize()
	{
	MEMORYSTATUS MS;
	GlobalMemoryStatus(&MS);
	return (double) MS.dwTotalPhys;
	}

static unsigned g_uMaxMemUseBytes;

unsigned GetMaxMemUseBytes()
	{
	return g_uMaxMemUseBytes;
	}

unsigned GetMemUseBytes()
	{
	HANDLE hProc = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS PMC;
	BOOL bOk = GetProcessMemoryInfo(hProc, &PMC, sizeof(PMC));
	if (!bOk)
		return 1000000;
	unsigned uBytes = (unsigned) PMC.WorkingSetSize;
	if (uBytes > g_uMaxMemUseBytes)
		g_uMaxMemUseBytes = uBytes;
	return uBytes;
	}

#endif
