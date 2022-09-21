/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: fcntl.h
* Note: (1) many macros defined in /usr/include/fcntl.h  
*           are to be defined here 
************************************************************/
#ifndef _SYS_FCNTL_H_
#define _SYS_FCNTL_H_

#include <sys/types.h>
#include <ch/sys/fcntl.h>

extern restrict int creat(const char *path, mode_t mode);
extern int fcntl(int, int, ...); 
/* generic function */
extern restrict int open(const char *path, int oflag, /* mode_t mode */...);

#endif /* _SYS_FCNTL_H_ */
