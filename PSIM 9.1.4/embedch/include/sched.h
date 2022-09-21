/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: sched.h
************************************************************/
#ifndef _SCHED_H_
#define _SCHED_H_

#include <sys/time.h>

struct sched_param {
	int	sched_priority;	/* process execution scheduling priority */
	int	sched_pad[8];	/* sizeof(sched_param) ==		*/
				/*	sizeof(sched_priority) +	*/
				/*	sizeof(pcparms_t.pc_clparms)	*/
};

/*
 *	POSIX scheduling policies
 */
#define	SCHED_OTHER	0
#define	SCHED_FIFO	1
#define	SCHED_RR	2

/*
 * function prototypes
 */
int	sched_getparam(pid_t pid, struct sched_param *param);
int	sched_setparam(pid_t pid, const struct sched_param *param);
int	sched_getscheduler(pid_t pid);
int	sched_setscheduler(pid_t pid, int policy,
		const struct sched_param *param);
int	sched_yield(void);
int	sched_get_priority_max(int policy);
int	sched_get_priority_min(int policy);
int	sched_get_rr_get_interval(pid_t pid, struct timespec *interval);


#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSched_handle = dlopen("libsched.dl", RTLD_LAZY);
if(_ChSched_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSched_handle in sched.h\n");
   exit(-1);
} 
void _dlclose_sched(void) {
   dlclose(_ChSched_handle);
}
atexit(_dlclose_sched);
#endif

#endif /* _SCHED_H_ */
