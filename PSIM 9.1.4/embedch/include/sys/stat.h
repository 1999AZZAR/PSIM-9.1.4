/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: stat.h
************************************************************/
#ifndef _SYS_STAT_H_
#define	_SYS_STAT_H_

#include <sys/types.h>
#ifndef _WIN32_
#include <sys/time.h>
#endif
#include <ch/sys/stat.h>

extern restrict int stat(const char *, struct stat *);
extern restrict int fstat(int fildes, struct stat *buf);
extern restrict int lstat(const char *path, struct stat *buf);
extern restrict int fchmod(int fildes, mode_t mode);
extern int mkfifo(const char *path, mode_t mode);
/* these could be shell commands instead of functions */
#ifndef CHWHICHCOMMAND
extern restrict int chmod(const char *path, mode_t mode);
extern restrict int mkdir(char *, mode_t);

/* generic function */
extern restrict mode_t umask(mode_t);
#endif

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysStat_handle = dlopen("libstat.dl", RTLD_LAZY);
if(_ChSysStat_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysStat_handle in sys/stat.h\n");
   exit(-1);
} 
void _dlclose_sysstat(void) {
   dlclose(_ChSysStat_handle);
}
atexit(_dlclose_sysstat);
#endif

#endif	/* _SYS_STAT_H_ */
