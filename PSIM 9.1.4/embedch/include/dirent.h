/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: dirent.h
: Note: Ch dirent.h header file wraper
************************************************************/
#ifndef _DIRENT_H_
#define	_DIRENT_H_

#include <sys/types.h>
#include <ch/dirent.h>

extern restrict DIR     *opendir(const char *);
extern struct dirent    *readdir(DIR *);
extern int readdir_r(DIR *, struct dirent *, struct dirent **);
extern long             telldir(DIR *);
extern void             seekdir(DIR *, long);
extern void             rewinddir(DIR *);
extern int              closedir(DIR *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChDirent_handle = dlopen("libdirent.dl", RTLD_LAZY);
if(_ChDirent_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChDirent_handle in dirent.h\n");
   exit(-1);
} 
void _dlclose_dirent(void) {
   dlclose(_ChDirent_handle);
}
atexit(_dlclose_dirent);
#endif

#endif /* _DIRENT_H_ */
