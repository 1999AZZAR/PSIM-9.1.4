/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: pwd.h
************************************************************/
#ifndef _PWD_H_
#define _PWD_H_

#include <sys/types.h>
#include <stdio.h>

struct passwd {
	char	*pw_name;
	char	*pw_passwd;
	uid_t	pw_uid;
	gid_t	pw_gid;
	char	*pw_age;
	char	*pw_comment;
	char	*pw_gecos;
	char	*pw_dir;
	char	*pw_shell;
};

extern struct passwd *getpwuid(uid_t);		/* MT-unsafe */
extern struct passwd *getpwnam(const char *);	/* MT-unsafe */

extern struct passwd *getpwuid_r(uid_t,	 struct passwd *, char *, int);
extern struct passwd *getpwnam_r(const char *,struct passwd *, char *, int);
extern struct passwd *getpwent_r(struct passwd *, char *, int);
extern struct passwd *fgetpwent_r(FILE *,struct passwd *, char *, int);
extern void setpwent(void);
extern void endpwent(void);
extern struct passwd *getpwent(void);		/* MT-unsafe */
extern struct passwd *fgetpwent(FILE *);	/* MT-unsafe */
extern restrict int putpwent(const struct passwd *, FILE *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChPwd_handle = dlopen("libpwd.dl", RTLD_LAZY);
if(_ChPwd_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChPwd_handle in pwd.h\n");
   exit(-1);
}
void _dlclose_pwd(void) {
   dlclose(_ChPwd_handle);
}
atexit(_dlclose_pwd);
#endif

#endif /* _PWD_H_ */
