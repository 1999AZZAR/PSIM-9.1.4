/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: resource.h
************************************************************/
#ifndef _SYS_RESOURCE_H_
#define	_SYS_RESOURCE_H_

#include <sys/types.h>
#include <sys/time.h>

/*
 * Process priority specifications
 */
 
#define PRIO_PROCESS    0
#define PRIO_PGRP       1
#define PRIO_USER       2
#define PRIO_PRIV       -1

/*
 * Resource limits
 */

#define RLIMIT_CPU      0               /* cpu time in milliseconds */
#define RLIMIT_FSIZE    1               /* maximum file size */
#define RLIMIT_DATA     2               /* data size */
#define RLIMIT_STACK    3               /* stack size */
#define RLIMIT_CORE     4               /* core file size */
#if defined(_SUN_) || defined(_SOLARIS_)
#define RLIMIT_NOFILE   5               /* file descriptors */
#define RLIMIT_VMEM     6               /* maximum mapped memory */
#define RLIMIT_AS       RLIMIT_VMEM
#define RLIM_NLIMITS    7               /* number of resource limits */
#elif defined(_LINUX_) || defined(_LINUXPPC_)
#define RLIMIT_RSS      5               /* max resident set size */
#define RLIMIT_NPROC    6               /* max number of processes */
#define RLIMIT_NOFILE   7               /* max number of open files */
//#define RLIMIT_MEMLOCK 8               /* max locked-in-memory address space*/
#define RLIM_NLIMITS    8
#elif defined(_DARWIN_)
#define RLIMIT_RSS      5               /* max resident set size */
#define RLIMIT_MEMLOCK  6               /* max locked-in-memory address space*/
#define RLIMIT_NPROC    7               /* max number of processes */
#define RLIMIT_NOFILE   8               /* max number of open files */
#define RLIM_NLIMITS    9
#define PRIO_MIN        -20
#define PRIO_MAX        20
struct orlimit {
        int rlim_cur;               /* current (soft) limit */
        int rlim_max;               /* maximum value for rlim_cur */
};
/* Load average structure. */
struct loadavg {
        unsigned int ldavg[3];
        long    fscale;
};
#elif defined(_LYNX_)
#define RLIMIT_STACK    0
#define RLIMIT_DATA     1
#define RLIMIT_CORE     2
#define RLIMIT_FSIZE    3
#define RLIMIT_THREAD   4
#else /* default */
#define RLIMIT_RSS      5               /* resident set size */
#define RLIM_NLIMITS    6               /* number of resource limits */
#endif

#define RLIM_INFINITY   0x7fffffff

typedef int rlim_t;
struct rlimit {
        rlim_t  rlim_cur;               /* current limit */
        rlim_t  rlim_max;               /* maximum value for rlim_cur */
};

#define RUSAGE_SELF     0
#define RUSAGE_CHILDREN -1
#define RUSAGE_BOTH -2

struct  rusage {
  struct timeval ru_utime;
  struct timeval ru_stime; 
  long    ru_maxrss;
  long    ru_ixrss;
  long    ru_idrss;
  long    ru_isrss;
  long    ru_minflt;
  long    ru_majflt;
  long    ru_nswap;
  long    ru_inblock;
  long    ru_oublock;
  long    ru_msgsnd;
  long    ru_msgrcv;
  long    ru_nsignals;
  long    ru_nvcsw;
  long    ru_nivcsw;
};

int getrusage(int who, struct rusage *r_usage);
extern int getpriority(int which, int who);
extern restrict int setpriority(int which, int who, int prio);
extern int getrlimit(int resource, struct rlimit *rlp);

/* generic function */
extern restrict int setrlimit(int resource, const struct rlimit *rlp);  

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysResource_handle = dlopen("libresource.dl", RTLD_LAZY);
if(_ChSysResource_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysResource_handle in resource.h\n");
   exit(-1);
} 
void _dlclose_sysresource(void) {
   dlclose(_ChSysResource_handle);
}
atexit(_dlclose_sysresource);
#endif

#endif	/* _SYS_RESOURCE_H_ */

