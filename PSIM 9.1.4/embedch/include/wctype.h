/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: wctype.h
************************************************************/
#ifndef _WCTYPE_H_
#define _WCTYPE_H_

#include <stddef.h>

#ifndef _WINT_T
#define _WINT_T
typedef wchar_t wint_t;
#endif  /* !_WINT_T */

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef wchar_t wctype_t;
#endif

typedef unsigned int	wctrans_t;

#ifndef WEOF
#define	WEOF	((wint_t) (-1))
#endif

extern	int iswalpha(wint_t);
extern	int iswupper(wint_t);
extern	int iswlower(wint_t);
extern	int iswdigit(wint_t);
extern	int iswxdigit(wint_t);
extern	int iswalnum(wint_t);
extern	int iswspace(wint_t);
extern	int iswpunct(wint_t);
extern	int iswprint(wint_t);
extern	int iswgraph(wint_t);
extern	int iswcntrl(wint_t);
/* tow* also become functions */
extern	wint_t towlower(wint_t);
extern	wint_t towupper(wint_t);
extern	wctrans_t wctrans(const char *);
extern	wint_t towctrans(wint_t, wctrans_t);
extern  int iswctype(wint_t, wctype_t);
extern  wctype_t wctype(const char *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChWctype_handle = dlopen("libwctype.dl", RTLD_LAZY);
if(_ChWctype_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChWctype_handle in wctype.h\n");
   exit(-1);
}
void _dlclose_wtype(void) {
   dlclose(_ChWctype_handle);
}
atexit(_dlclose_wtype);
#endif

#endif	/* _WCTYPE_H_ */
