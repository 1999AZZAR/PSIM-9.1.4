/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: syslog.h
: Note: CH syslog.h header file wraper
************************************************************/
#ifndef _SYSLOG_H_
#define	_SYSLOG_H_

#include <stdarg.h>

#include <ch/syslog.h>

extern void openlog(const char *, int, int);
extern void syslog(int, const char *, ...);
extern void closelog(void);
extern int setlogmask(int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSyslog_handle = dlopen("libsyslog.dl", RTLD_LAZY);
if(_ChSyslog_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSyslog_handle in syslog.h\n");
   exit(-1);
} 
void _dlclose_syslog(void) {
   dlclose(_ChSyslog_handle);
}
atexit(_dlclose_syslog);
#endif  
 
#endif /* _SYSLOG_H_ */
