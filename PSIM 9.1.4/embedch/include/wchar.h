/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: wchar.h
************************************************************/
#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <stdio.h>
#include <stddef.h>

#ifndef	_WINT_T
#define	_WINT_T
typedef	wchar_t wint_t;
#endif	/* !_WINT_T */

#ifndef	_WCTYPE_T
#define	_WCTYPE_T
typedef	wchar_t wctype_t;
#endif

#ifndef	WEOF
#define	WEOF	((wint_t) (-1))
#endif

#ifndef	WCHAR_MAX
#define	WCHAR_MAX	2147483647
#endif
#ifndef	WCHAR_MIN
#define	WCHAR_MIN	(-2147483647-1)
#endif

/* for Linux, memory is larger than Solaris's implementation */
typedef struct {
  int count;            /* Number of bytes needed for the current character. */
  wint_t value;         /* Value so far.  */
} mbstate_t;

#ifndef _TM_DEFINED
struct tm {
        int     tm_sec;
        int     tm_min;
        int     tm_hour;
        int     tm_mday;
        int     tm_mon;
        int     tm_year;
        int     tm_wday;
        int     tm_yday;
        int     tm_isdst;
};
#define _TM_DEFINED
#endif


extern int iswalpha(wint_t);
extern int iswupper(wint_t);
extern int iswlower(wint_t);
extern int iswdigit(wint_t);
extern int iswxdigit(wint_t);
extern int iswalnum(wint_t);
extern int iswspace(wint_t);
extern int iswpunct(wint_t);
extern int iswprint(wint_t);
extern int iswgraph(wint_t);
extern int iswcntrl(wint_t);
extern int iswctype(wint_t, wctype_t);
extern wint_t towlower(wint_t);
extern wint_t towupper(wint_t);
extern wint_t fgetwc(FILE *);
extern wchar_t *fgetws(wchar_t *, int, FILE *);
extern wint_t fputwc(wint_t, FILE *);
extern int fputws(const wchar_t *, FILE *);
extern wint_t ungetwc(wint_t, FILE *);
extern wint_t getwc(FILE *);
extern wint_t getwchar(void);
extern wint_t putwc(wint_t, FILE *);
extern wint_t putwchar(wint_t);
extern double wcstod(const wchar_t *, wchar_t **);
extern long wcstol(const wchar_t *, wchar_t **, int);
extern unsigned long wcstoul(const wchar_t *, wchar_t **, int);
extern wchar_t *wcscat(wchar_t *, const wchar_t *);
extern wchar_t *wcschr(const wchar_t *, wchar_t);
extern int wcscmp(const wchar_t *, const wchar_t *);
extern int wcscoll(const wchar_t *, const wchar_t *);
extern wchar_t *wcscpy(wchar_t *, const wchar_t *);
extern size_t wcscspn(const wchar_t *, const wchar_t *);
extern size_t wcslen(const wchar_t *);
extern wchar_t *wcsncat(wchar_t *, const wchar_t *, size_t);
extern int wcsncmp(const wchar_t *, const wchar_t *, size_t);
extern wchar_t *wcsncpy(wchar_t *, const wchar_t *, size_t);
extern wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
extern wchar_t *wcsrchr(const wchar_t *, wchar_t);
extern size_t wcsspn(const wchar_t *, const wchar_t *);
extern wchar_t *wcswcs(const wchar_t *, const wchar_t *);
extern int wcswidth(const wchar_t *, size_t);
extern size_t wcsxfrm(wchar_t *, const wchar_t *, size_t);
extern int wcwidth(const wchar_t);
extern wctype_t wctype(const char *);
extern wchar_t *wcstok(wchar_t *, const wchar_t *, wchar_t **);
/* extern wchar_t *wcstok(wchar_t *, const wchar_t *); in some older compilers */
extern size_t wcsftime(wchar_t *, size_t, const wchar_t *, const struct tm *);

extern wint_t	btowc(int);
extern int	fwide(FILE *, int);
extern int	mbsinit(const mbstate_t *);
extern size_t	mbrlen(const char *, size_t, mbstate_t *);
extern size_t	mbrtowc(wchar_t *, const char *, size_t, mbstate_t *);
extern size_t	mbsrtowcs(wchar_t *, const char **, size_t, mbstate_t *);
extern size_t	wcrtomb(char *, wchar_t, mbstate_t *);
extern size_t	wcsrtombs(char *, const wchar_t **, size_t, mbstate_t *);
extern wchar_t	*wcsstr(const wchar_t *, const wchar_t *);
extern int	wctob(wint_t);
extern wchar_t	*wmemchr(const wchar_t *, wchar_t, size_t);
extern int	wmemcmp(const wchar_t *, const wchar_t *, size_t);
extern wchar_t	*wmemcpy(wchar_t *, const wchar_t *, size_t);
extern wchar_t	*wmemmove(wchar_t *, const wchar_t *, size_t);
extern wchar_t	*wmemset(wchar_t *, wchar_t, size_t);
extern wchar_t	*wgetenv(wchar_t *name);

extern int	fwprintf(FILE *, const wchar_t *, ...);
extern int	swprintf(wchar_t *, size_t, const wchar_t *, ...);
extern int	wprintf(const wchar_t *, ...);
extern int	vfwprintf(FILE *, const wchar_t *, va_list);
extern int	vswprintf(wchar_t *, size_t, const wchar_t *, va_list);
extern int	vwprintf(const wchar_t *, va_list);
#ifdef _SOLARIS_
extern int      wsprintf(wchar_t *s, const char *format, /* arg  */  ...);
#endif

//extern int    wsscanf(wchar_t *s, const char *format,  /*  pointer  */ ... );
//extern int	fwscanf(FILE *, const wchar_t *, ...);
//extern int	swscanf(const wchar_t *, const wchar_t *, ...);
//extern int	wscanf(const wchar_t *, ...);

#define watoi(s)    ((int)wcstol((s), (wchar_t **)0, 10))
#define watol(s)    wcstol((s), (wchar_t **)0, 10)
//#define watoll(s) wcstoll((s), (wchar_t **)0, 10)
#define watof(s)    wcstod((s), (wchar_t **)0)

#if defined(_WIN32_)
extern FILE *_wfopen(const wchar_t *filename, const wchar_t *mode);
#endif

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChWchar_handle = dlopen("libwchar.dl", RTLD_LAZY);
if(_ChWchar_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChWchar_handle in wchar.h\n");
   exit(-1);
}
void _dlclose_wchar(void) {
   dlclose(_ChWchar_handle);
}
atexit(_dlclose_wchar);
#endif	

#endif	/* _WCHAR_H_ */
