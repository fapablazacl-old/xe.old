
#ifndef __glad_h__
#define __glad_h__

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#ifdef _DEBUG
#include "glad_debug.h"
#else 
#include "glad_release.h"	
#endif 

#endif
