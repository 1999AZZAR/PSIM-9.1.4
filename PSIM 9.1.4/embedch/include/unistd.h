/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: unistd.h
: Note: Unix standard header file
************************************************************/
#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <sys/types.h>
#include <ch/unistd.h>

#define R_OK   4       /* Test for Read permission */
#define W_OK   2       /* Test for Write permission */
#define X_OK   0       /* Test for eXecute permission */
#define F_OK   0       /* Test for existence of File */


#define F_ULOCK 0       /* Unlock a previously locked region */
#define F_LOCK  1       /* Lock a region for exclusive use */
#define F_TLOCK 2       /* Test and lock a region for exclusive use */
#define F_TEST  3       /* Test a region for other processes locks */

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

//extern int access(const char *, int);
extern char *ctermid(char *);
extern char *cuserid(char *);
extern restrict int execl(char *path, char *arg0, ...);
extern restrict int execle(char *path, char *arg0, ...);
extern restrict int execlp(char *file, char *arg0, ...);
extern restrict int execv(char *path, char **argv);
extern restrict int execve (char *path, char *argv[], char *envp[]);
extern restrict int execvp(char *file, char **argv); 
extern restrict int fchdir(int);
extern restrict int fchown(int, uid_t, gid_t);
extern restrict int fchroot(int);
extern restrict pid_t fork(void);
extern long fpathconf(int fildes, int);
extern int fsync(int);
extern int ftruncate(int, off_t);
extern char *getcwd(char *, size_t);
extern gid_t getegid(void);
extern uid_t geteuid(void);
extern gid_t getgid(void);
extern int getgroups(int, gid_t *);
extern int long gethostid(void);
extern restrict int gethostname(char *name, int namelen);
extern char *getlogin(void);
extern char *getlogin_r(char *, int);
extern pid_t getpid(void);
extern pid_t getpgid(pid_t);
extern pid_t getppid(void);
extern pid_t getpgrp(void);
char *gettxt(const char *, const char *);
extern pid_t getsid(pid_t);
extern uid_t getuid(void);
extern int isatty(int);
extern restrict int lchown(const char *, uid_t, gid_t);
extern off_t lseek(int fildes, off_t offset, int whence); 
extern int mincore(caddr_t, size_t, char *);
extern long pathconf(const char *, int);
extern int pause(void);
extern restrict int pipe(int fildes[2]);
extern void profil(unsigned short *, unsigned int, unsigned int, unsigned int);
extern int ptrace(int, pid_t, int, int);
extern int readlink(const char *, void *, size_t);
extern void *sbrk(int);
extern int setgid(gid_t);
extern int setegid(gid_t);
extern int setgroups(int, const gid_t *);
extern int setpgid(pid_t, pid_t);
extern pid_t setpgrp(void);
extern pid_t setsid(void);
extern int setuid(uid_t);
extern int seteuid(uid_t);
extern unsigned int sleep(unsigned int seconds);
extern int usleep(useconds_t useconds);
extern int stime(const time_t *);
extern int symlink(const char *, const char *);
extern void sync(void);
extern long sysconf(int);
extern pid_t tcgetpgrp(int);
extern int tcsetpgrp(int, pid_t);
extern int truncate(const char *, off_t);
extern char *ttyname(int);
extern char *ttyname_r(int, char *, int);
extern restrict pid_t vfork(void);
extern void vhangup(void);
extern int dup(int fildes);
extern int dup2(int fildes, int fildes2);
extern int getopt(int argc, char **argv, char *optstring);
extern char *optarg;
extern int  opterr, optind, optopt;

/* these could be shell commands instead of functions */
#ifndef CHWHICHCOMMAND
extern int acct(const char *);
extern unsigned alarm(unsigned);
extern restrict int chdir(const char *);
extern restrict int chown(const char *, uid_t, gid_t);
extern restrict int chroot(const char *);
extern restrict int link(const char *, const char *);
extern int nice(int);
extern restrict int rmdir(const char *);
extern restrict int unlink(const char *);
extern ssize_t write(int, const void *, size_t);

/* generic function */
ssize_t read(int fildes, void *buf, size_t nbyte);
#endif


#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChUnistd_handle = dlopen("libunistd.dl", RTLD_LAZY);
if(_ChUnistd_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChUnistd_handle in unistd.h\n");
   exit(-1);
}
void _dlclose_unistd(void) {
   dlclose(_ChUnistd_handle);
}
atexit(_dlclose_unistd);
#endif 

#endif  /* _UNISTD_H_  */
