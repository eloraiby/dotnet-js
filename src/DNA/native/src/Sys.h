// Copyright (c) 2012 DotNetAnywhere
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#if !defined(__SYS_H)
#define __SYS_H

#include "Config.h"

#if defined(DIAG_MEMORY_LEAKS) && defined(_WIN32)
// looking for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

/*#ifdef _DEBUG
void* mallocTrace(int s, char *pFile, int line);
#define malloc(s) mallocTrace(s, __FILE__, __LINE__)
#endif*/

#ifdef _DEBUG
#define Assert(cond) if (!(cond)) Crash("Assert failed: %s, line %d", __FILE__, __LINE__);
#else
#define Assert(cond)
#endif

#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#define dprintf(format, ...) printf(format, __VA_ARGS__)
#define dprintfn(format, ...) printf(format "\n", __VA_ARGS__)
#else
#define dprintf(format, ...) ((void) 0)
#define dprintfn(format, ...) ((void) 0)
#endif

#define FAKE_RETURN exit(101)

#define INTERNALCALL_PARAM(ofs, type) *(type*)(pParams + ofs)

#include "MetaData.h"

void Crash(char *pMsg, ...);

extern U32 logLevel;
void log_f(U32 level, const char *pMsg, ...);

void printbuf(const char* format, ...);
void PrintBufferContents();

char* Sys_GetMethodDesc(tMD_MethodDef *pMethod);

void* mallocForever(U32 size);
void* callocForever(U32 count, U32 size);
void freeForever();

#ifdef _WIN32
//#define GetTicks() __rdtsc()
U64 GetTicks();
double TicksToSeconds(U64 ticks);
#endif

U64 microTime();
U64 msTime();
void SleepMS(U32 ms);

#ifdef DEBUG_PRINT
char* Sys_CIL_OpCodeName(U32 op);
char* Sys_JIT_OpCodeName(U32 op);
#endif

#endif
