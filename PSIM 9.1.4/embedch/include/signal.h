/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: signal.h
: Note: CH signal.h header file wraper
************************************************************/
#ifndef _SIGNAL_H_
#define	_SIGNAL_H_

#include <ch/signal.h>

extern void (*signal(int, void (*) (int)))(int);
extern int raise(int);
extern restrict int kill(pid_t, int);
#if _isvar("sigset_t")
extern int sigemptyset(sigset_t *);
extern int sigfillset(sigset_t *);
extern int sigaddset(sigset_t *, int);
extern int sigdelset(sigset_t *, int);
extern int sigismember(const sigset_t *, int);
extern int sigaction(int, const struct sigaction *, struct sigaction *);
extern int sigprocmask(int, const sigset_t *, sigset_t *);
extern int sigsuspend(const sigset_t *);
extern int sigpending(sigset_t *);
#if _isvar("siginfo_t")
extern int sigwaitinfo(const sigset_t *set, siginfo_t *info);
#if _isvar("timespec")
extern int sigtimedwait(const sigset_t *set, siginfo_t * info,
			const struct timespec *timeout);
#endif
#endif
#endif
#if _isvar("sigval")
extern int sigqueue(pid_t pid, int signo, const union sigval value);
#endif
#if _isvar("stack_t")
extern int sigaltstack(const stack_t *, stack_t *); 
#endif
extern int siginterrupt(int, int);
extern void (*sigset(int, void (*)(int)))(int);
extern int sighold(int);
extern int sigrelse(int);
extern int sigignore(int);
extern int sigpause(int);
extern long sigblock(long);
extern long sigsetmask(long);
extern int (*ssignal(int, int (*) (int)))(int);
extern ssize_t sigspace(size_t);
extern int gsignal(int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSignal_handle = dlopen("libsignal.dl", RTLD_LAZY);
if(_ChSignal_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSignal_handle in signal.h\n");
   exit(-1);
} 
void _dlclose_signal(void) {
   dlclose(_ChSignal_handle);
}
atexit(_dlclose_signal);
#endif 

#endif /* _SIGNAL_H_ */
