#pragma once

#ifndef __xe_predef_hpp__
#define __xe_predef_hpp__

#if defined(_WINDOWS)
  #define XE_API_EXPORT __declspec(dllexport)
  #define XE_API_IMPORT __declspec(dllimport)
#else 
  #define XE_API_EXPORT
  #define XE_API_IMPORT
#endif

#if defined(XE_SHARED)
  #if defined(XE_BUILD)
    #define XE_API XE_API_EXPORT
  #else
    #define XE_API XE_API_IMPORT
  #endif
#else 
  #define XE_API 
#endif

#endif
