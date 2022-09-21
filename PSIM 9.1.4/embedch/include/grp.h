/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: grp.h
************************************************************/
#ifndef _GRP_H_
#define _GRP_H_

#include <sys/types.h>
#include <stdio.h>

struct	group {	
	char	*gr_name;
	char	*gr_passwd;
	gid_t	gr_gid;
	char	**gr_mem;
};

extern struct group *getgrnam(const char *name);
extern struct group *getgrent(void);
extern struct group *getgrgid(gid_t gid);
extern void setgrent(void);
extern void endgrent(void);
extern struct group *fgetgrent(FILE *f);
extern int initgroups(const char *name, gid_t basegid);

#if defined(_LINUX_) || defined(_LINUXPPC_) || defined(_FREEBSD_) || defined(_QNX_) 
extern int getgrent_r(struct group * resultbuf, char * buffer, size_t buflen,
                      struct group ** result);
extern int getgrgid_r(gid_t gid, struct group * resultbuf, char * buffer, size_t buflen,
                      struct group ** result);
extern int getgrnam_r(char * name, struct group * resultbuf,
                      char * buffer, size_t buflen, struct group ** result);
extern int fgetgrent_r(FILE * stream, struct group * resultbuf,
                       char * buffer, size_t buflen, struct group ** result);
#else
extern int getgrent_r(struct group *result, char *buffer,
          int buflen, struct group **);
extern struct group *getgrnam_r(const char *name,
           struct group *result,  char *buffer, int buflen);
extern struct group *getgrgid_r(gid_t gid, struct group *result,
           char *buffer, int buflen);
extern struct group *fgetgrent_r(FILE *f, struct group *result,
           char *buffer, int buflen);
#endif


#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChGrp_handle = dlopen("libgrp.dl", RTLD_LAZY);
if(_ChGrp_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChGrp_handle in grp.h\n");
   exit(-1);
}
void _dlclose_grp(void) {
   dlclose(_ChGrp_handle);
}
atexit(_dlclose_grp);
#endif

#endif /* _GRP_H_ */
