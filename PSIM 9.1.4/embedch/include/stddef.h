/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: stddef.h
: Note: standard definition header file
************************************************************/
#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
#ifdef _M64_
typedef long long ptrdiff_t;
#else
typedef int     ptrdiff_t;
#endif

#endif

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#ifdef _M64_
typedef unsigned long long size_t;  
#else
typedef unsigned int    size_t;         /* (historical version) */
#endif
#endif  /* !_SIZE_T_DEFINED */

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#if defined(_WIN32_)
typedef unsigned short wchar_t;
#else
typedef int wchar_t;
#endif
#endif  /* !_WCHAR_T_DEFINED */


#define offsetof(s, m)  (size_t)(&(((s *)0)->m))

#endif /* _STDDEF_H_ */
