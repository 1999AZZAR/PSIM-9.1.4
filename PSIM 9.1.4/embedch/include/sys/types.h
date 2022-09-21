/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/* Copyright (c) 2001-2008 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: types.h
************************************************************/
#ifndef _SYS_TYPES_H_
#define	_SYS_TYPES_H_


#if defined(_SOLARIS_) || defined(_LINUX_) || defined(_LINUXPPC_) || defined(_QNX_) || defined(_AIX_)
typedef unsigned int mode_t;  /* For file types and modes */
#else
typedef unsigned short mode_t; /* For file types and modes */
#endif

#if defined(_LINUX_) || defined(_LINUXPPC_) || defined(_FREEBSD_) || defined(_AIX_) 
typedef long long dev_t;       /* For device numbers */
#else
typedef int dev_t;             /* For device numbers */
#endif

#if defined(_LINUX_) || defined(_LINUXPPC_) 
typedef unsigned long nlink_t;   /* For link counts */
#elif defined(_SOLARIS_) || defined(_QNX_) 
typedef unsigned int nlink_t;    /* For link counts */
#else
typedef unsigned short nlink_t;  /* For link counts */
#endif
typedef int pid_t;             /* For process and session IDs */
typedef int gid_t;             /* For group IDs */
typedef int key_t;             /* IPC key type         */
typedef unsigned int   __udev_t; 
#if defined(_WIN32_)
typedef unsigned short ino_t;  /* For file serial numbers */
#elif defined(_AIX_)
typedef unsigned long long ino_t;    /* For file serial numbers */
#elif !defined(_SOLARIS_)
typedef unsigned long ino_t;    /* For file serial numbers */
#endif

#ifndef _SSIZE_T_DEFINED  
#define _SSIZE_T_DEFINED
#ifdef _M64_
typedef long long ssize_t;  
#else
typedef int ssize_t;           /* Signed version of size_t */
#endif
#endif

#ifndef _SIZE_T_DEFINED  
#define _SIZE_T_DEFINED
#ifdef _M64_
typedef unsigned long long size_t;  /* len param for string funcs */
#else
typedef unsigned int  size_t;   /* len param for string funcs */
#endif
#endif

#ifndef _TIME_T
#define _TIME_T
#if defined(_M64_) || defined(_WIN32_)
typedef long long time_t; 
#else
typedef int  time_t; 
#endif
#endif  

#ifndef _CLOCK_T
#define _CLOCK_T
#ifdef _M64_
typedef long long clock_t;
#else
typedef int  clock_t;
#endif
#endif

#ifndef _UID_T
#define _UID_T
typedef int uid_t;             /* For user IDs */
#endif

typedef long            t_scalar_t;     /* historical versions */
typedef unsigned long   t_uscalar_t;

/* POSIX */
typedef unsigned char   uchar_t;
typedef unsigned short  ushort_t;
typedef unsigned int    uint_t;
typedef unsigned long   ulong_t;

typedef char *          caddr_t;        /* ?<core address> type */
#if defined(_AIX_)
typedef long long       daddr_t;        /* <disk address> type */
typedef long long       off_t;     /* ?<offset> type */
                                        /* For file offsets and sizes */
#else
typedef int             daddr_t;        /* <disk address> type */
typedef long            off_t;          /* ?<offset> type */
#endif
typedef short           cnt_t;          /* ?<count> type */

typedef ulong_t         paddr_t;        /* <physical address> type */
typedef uchar_t         use_t;          /* use count for swap.  */
typedef short           sysid_t;
typedef short           index_t;

typedef uint_t          useconds_t;     /* Time, in microseconds */

/* used to reserve space and generate alignment */
typedef long long longlong_t;
typedef unsigned long long u_longlong_t;

/* System V */
#if !_isvar("unchar")
typedef unsigned char   unchar;
#endif
#if !_isvar("ushort")
typedef unsigned short  ushort;
#endif
#if !_isvar("uint")
typedef unsigned int    uint;
#endif
#if !_isvar("ulong")
typedef unsigned long   ulong;
#endif

/* BSD */
#ifndef BSD_UNSIGNED /* these typedef are also defined in winsock2.h */
#define BSD_UNSIGNED
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
#endif /* BSD_UNSIGNED */

#if defined(_DARWIN_) || defined(_FREEBSD_)
typedef unsigned char   u_int8_t;
typedef unsigned short  u_int16_t;
typedef unsigned int    u_int32_t;
typedef unsigned long long u_int64_t;
#endif


typedef longlong_t      offset_t;
typedef longlong_t      diskaddr_t;

/*
 * Partial support for 64-bit file offset enclosed herein,
 * specifically used to access devices greater than 2gb.
 * However, support for devices greater than 2gb requires compiler
 * support for long long.
 * XXX These assume big-endian machines XXX
 */
typedef union lloff {
        offset_t        _f;     /* Full 64 bit offset value */
        struct {
                long _u;        /* upper 32 bits of offset value */
                off_t _l;       /* lower 32 bits of offset value */
        } _p;
} lloff_t;

typedef union lldaddr {
        diskaddr_t      _f;     /* Full 64 bit disk address value */
        struct {
                long _u;        /* upper 32 bits of disk address value */
                daddr_t _l;     /* lower 32 bits of disk address value */
        } _p;
} lldaddr_t;

typedef ulong_t k_fltset_t;     /* kernel fault set type */

/*
 * The following type is for various kinds of identifiers.  The
 * actual type must be the same for all since some system calls
 * (such as sigsend) take arguments that may be any of these
 * types.  The enumeration type idtype_t defined in sys/procset.h
 * is used to indicate what type of id is being specified.
 */
 
typedef long            id_t;           /* A process id,        */
                                        /* process group id,    */
                                        /* session id,          */
                                        /* scheduling class id, */
                                        /* user id, or group id */
 
 
/* Typedefs for dev_t components */
 
typedef ulong_t major_t;        /* major part of device number */
typedef ulong_t minor_t;        /* minor part of device number */
 
 
/* The data type of a thread priority. */
 
typedef short   pri_t;

#include <inttypes.h> 

#if defined(_SOLARIS_)
/* temp fix here, to be modified in the future for 64 bits */
#define _FILE_OFFSET_BITS 32
#if defined(_LP64) || _FILE_OFFSET_BITS == 32
typedef ulong_t         ino_t;          /* expanded inode type  */
typedef long            blkcnt_t;       /* count of file blocks */
typedef ulong_t         fsblkcnt_t;     /* count of file system blocks */
typedef ulong_t         fsfilcnt_t;     /* count of files */
#elif _FILE_OFFSET_BITS == 64
typedef u_longlong_t    ino_t;          /* expanded inode type  */
typedef longlong_t      blkcnt_t;       /* count of file blocks */
typedef u_longlong_t    fsblkcnt_t;     /* count of file system blocks */
typedef u_longlong_t    fsfilcnt_t;     /* count of files */
#endif
#ifdef _LP64
typedef int             blksize_t;      /* used for block sizes */
#else
typedef long            blksize_t;      /* used for block sizes */
#endif

#elif defined(_HPUX_) || defined(_LINUX_) || defined(_LINUXPPC_)
typedef long long blkcnt_t;  /* 32-bit # of blocks */

#elif defined(_AIX_)
#ifdef _M64_
typedef long long blkcnt_t;  /* 64-bit # of blocks */
typedef long long blksize_t;  /* 64-bit # of blocks */
#else
typedef long blkcnt_t;       /* 32-bit # of blocks */
typedef long blksize_t;       /* 32-bit # of blocks */
#endif

#endif


#endif	/* _SYS_TYPES_H_ */

