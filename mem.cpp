#include "piler2.h"
#define __STDC_LIMIT_MACROS
#include <stdint.h>

#ifdef	_MSC_VER
#include <crtdbg.h>
#endif

static size_t AllocatedBytes;
static size_t PeakAllocatedBytes;
static const size_t numTrackingBytes = sizeof(size_t);

// Allocate memory, fail on error, track total
void *allocmem(size_t bytes)
	{
	// Ensure we can extend the allocation to include the size tracker
	assert((SIZE_MAX - bytes) >= numTrackingBytes);

	char *p = (char *) malloc(bytes + numTrackingBytes);
	if (0 == p)
		Quit("ERROR: Failed to allocate memory (%llu bytes).", bytes);

	// Store the allocation size into the first size_t bytes
	size_t *pSize = (size_t *) p;
	*pSize = bytes;
	AllocatedBytes += bytes;
	if (AllocatedBytes > PeakAllocatedBytes)
		PeakAllocatedBytes = AllocatedBytes;
	// Advance the pointer beyond the tracker before returning
	return p + numTrackingBytes;
	}

void freemem(void *p)
	{
	if (0 == p)
		return;
	size_t *pSize = ((size_t *) p) - 1;
	size_t numDataBytes = *pSize;
	assert(numDataBytes <= AllocatedBytes);
	AllocatedBytes -= numDataBytes;
	// Also free the tracker
	free((size_t *) p - 1);
	}

void chkmem()
	{
#ifdef	_MSC_VER
	assert(_CrtCheckMemory());
#endif
	}

void *reallocmem(void *pOldAlloc, size_t bytes)
	{
	if (0 == pOldAlloc)
		return allocmem(bytes);
	size_t *pOldAllocSize = (size_t *) pOldAlloc - 1;
	void *pNewAlloc = allocmem(bytes);
	memcpy(pNewAlloc, pOldAlloc, *pOldAllocSize);
	return pNewAlloc;
	}
