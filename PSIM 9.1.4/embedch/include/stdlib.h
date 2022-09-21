/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: stdlib.h
: Note: standard lib header file
************************************************************/
#ifndef _STDLIB_H_
#define _STDLIB_H_

#define EXIT_FAILURE  1       /* Failing exit status.  */
#define EXIT_SUCCESS  0       /* Successful exit status.  */
#define MB_CUR_MAX    _MB_CUR_MAX
#define RAND_MAX      _RAND_MAX

typedef struct {
        int     quot;
        int     rem;
} div_t;

typedef struct {
        int    quot;
        int    rem;
} ldiv_t;

#if !_isvar("size_t")
#define _SIZE_T_DEFINED
#ifdef _M64_
typedef unsigned long long size_t;  
#else
typedef unsigned int    size_t;      
#endif
#endif

#if !_isvar("uid_t")
#define _UID_T
typedef int   uid_t;
#endif

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#if defined(_WIN32_)
typedef unsigned short wchar_t;
#else
typedef int wchar_t;
#endif
#endif  /* !_WCHAR_T_DEFINED */


extern double complex atoc(const char *);
extern double atof(const char *);
extern int atoi(const char *);
extern long int atol(const char *);

extern int rand(void);
extern void srand(unsigned int);

extern void *calloc(size_t, size_t);
extern void *malloc(size_t);
extern void *realloc(void *, size_t);

extern void abort(void);
extern int atexit(void (*)(void));
if(_prompt == NULL)  {
  extern void exit(int);
}
extern restrict int system(const char *);

extern void *bsearch(const void *, const void *, size_t, size_t,
	int (*)(const void *, const void *));
extern void qsort(void *, size_t, size_t,
	int (*)(const void *, const void *));

extern div_t div(int, int);
extern long int labs(long);
extern ldiv_t ldiv(long, long);

extern int mbtowc(wchar_t *, const char *, size_t);
extern int mblen(const char *, size_t);
extern int wctomb(char *, wchar_t);

extern size_t mbstowcs(wchar_t *, const char *, size_t);
extern size_t wcstombs(char *, const wchar_t *, size_t);

extern void abort(void);
extern int atexit(void (*func)(void));
extern char *mktemp(char *template);
extern int mkstemp(char *template);

extern int getopt(int argc, char **argv, char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

/* Ch only */
extern int iscnum(char *pattern);
extern int isenv(char *name);
extern int isnum(char *pattern);
extern int iswnum(wchar_t *pattern);
extern int remenv(char *name);

extern long long strtoll(const char *str, char **endptr, int base);
extern long long atoll(const char *str);

/* generic functions */
extern int abs(int val);
extern void free(void *ptr);
extern char *getenv(const char *name); 
extern double strtod(const char *str, char **endptr);
extern long strtol(const char *str, char **endptr, int base);
extern unsigned long strtoul(const char *str, char **endptr, int base);


#if defined(_WIN32_)
extern void _sleep(unsigned long);
#if !defined(_M_MPPC) && !defined(_M_M68K)
#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */
#else   /* defined(_M_M68K) || defined(_M_MPPC) */
#define _MAX_PATH   256 /* max. length of full pathname */
#define _MAX_DIR    32  /* max. length of path component */
#define _MAX_FNAME  64  /* max. length of file name component */
#endif  /* defined(_M_M68K) || defined(_M_MPPC) */
#endif // _WIN32_

#if defined(_CHDLL_)
#include <dlfcn.h>
char **environ;
extern void *_ChStdlib_handle = dlopen("libstdlib.dl", RTLD_LAZY);
if(_ChStdlib_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChStdlib_handle in stdlib.h\n");
   exit(-1);
} 
else {
   void *fptr, ChStdlib_hInitialize(char ***environ);
    fptr = dlsym(_ChStdlib_handle , "ChStdlib_hInitialize");
    if(fptr == NULL) { 
       fprintf(_stderr, "Error: dlsym(): ChStdlib_hInitialize() in stdlib.h: %s\n", dlerror());
       exit(1);
    }
    dlrunfun(fptr, NULL, ChStdlib_hInitialize, &environ);
}
void _dlclose_stdlib(void) {
   dlclose(_ChStdlib_handle);
}
atexit(_dlclose_stdlib);
#endif

#endif /* _STDLIB_H_ */
