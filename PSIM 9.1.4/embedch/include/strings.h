/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: string.h
: Note: string header file
************************************************************/
#ifndef _STRING_H_
#define _STRING_H_

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#ifdef _M64_
typedef unsigned long long size_t;  
#else
typedef unsigned int    size_t;      
#endif
#endif

extern int memcmp(const void *, const void *, size_t);
extern int strncmp(const char *, const char *, size_t);

extern void *memchr(const void *, int, size_t);
extern char *strchr(const char *, int);
extern size_t strcspn(const char *, const char *);
extern char * strdup(const char * s);
extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);
extern size_t strspn(const char *, const char *);
extern char *strstr(const char *, const char *);
extern char *strtok_r(char *, const char *, char **);
extern int strcasecmp(char *s1, char *s2);
extern int strncasecmp(char *s1, char *s2, int n);

extern int bcmp(const void *s1, const void *s2, size_t n);
extern void bcopy(const void *s1, void *s2, size_t n);
extern void bzero(char *s, int n);

extern char* strjoin(const char *separator, ...);
extern char* strconcat (const char *string1, ...);


/* For Ch string_t */
extern unsigned int str2ascii(char *s);
extern int str2mat(char mat[:][:], string_t s1, ...);
extern char strgetc(string_t &s, int i);
extern int strputc(string_t &s, int i, char c);
extern string_t strrep(string_t s1, string_t s2, string_t s3);

/* generic functions */
extern void *memcpy(void *s1, const void *s2, size_t n);
extern void *memmove(void *s1, const void *s2, size_t n);
extern void *memset(void *s, int c, size_t n);
extern char *strcat(char *s1, const char *s2);
extern char *strncat(char *s1, const char *s2, size_t n);
extern char *strcpy(char *s1, const char *s2);
extern char *strncpy(char *s1, const char *s2, size_t n);
extern int strcmp(const char *s1, const char *s2);
extern char *strtok(char *s1, const char *s2);
extern int strcoll(const char *s1, const char *s2);
extern size_t strxfrm(char *s1, const char *s2, size_t n);
extern size_t strlen(const char *s);



#if defined(_CHDLL_)
#include <dlfcn.h>
extern void *_ChString_handle = dlopen("libstring.dl", RTLD_LAZY);
if(_ChString_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChString_handle in string.h\n");
   exit(-1);
}
void _dlclose_string(void) {
   dlclose(_ChString_handle);
}
atexit(_dlclose_string);
#endif

#endif /* _STRING_H_ */
