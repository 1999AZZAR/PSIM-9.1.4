/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: libintl.h
************************************************************/
#ifndef _LIBINTL_H_
#define _LIBINTL_H_

extern char *gettext(const char *msgid);
extern char *dgettext(const char *domainname, const char *msgid);
extern char *textdomain(const char *domainname);
extern char *bindtextdomain(const char *domainname, const char *dirname);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChLibintl_handle = dlopen("libintl.dl", RTLD_LAZY);
if(_ChLibintl_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChLibintl_handle in libintl.h\n");
   exit(-1);
} 
void _dlclose_linintl(void) {
   dlclose(_ChLibintl_handle);
}
atexit(_dlclose_libintl);
#endif

#endif	/* _LIBINTL_H_ */
