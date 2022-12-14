/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: cpio.h
************************************************************/
#ifndef _CPIO_H_
#define	_CPIO_H_

#define C_IRUSR       0000400  /* read by owner */
#define C_IWUSR       0000200  /* write by owner */
#define C_IXUSR       0000100  /* execute by owner */
#define C_IRGRP       0000040  /* read by group */
#define C_IWGRP       0000020  /* write by group */
#define C_IXGRP       0000010  /* execute by group */
#define C_IROTH       0000004  /* read by others */
#define C_IWOTH       0000002  /* write by others */
#define C_IXOTH       0000001  /* execute by others */
#define C_ISUID       0004000  /* set uid */
#define C_ISGID       0002000  /* set gid */
#define C_ISVTX       0001000  /* reserved */
#define C_ISDIR       0040000  /* directory */
#define C_ISFIFO      0010000  /* fifo */    
#define C_ISREG       0100000  /* regular file */
#define C_ISBLK       0060000  /* block special */
#define C_ISCHR       0020000  /* character special */
#define C_ISCTG       0110000  /* reserved */
#define C_ISLNK       0120000  /* symbolic link */
#define C_ISSOCK      0140000  /* socket */ 

#define MAGIC         "070707"

#endif /* _CPIO_H_ */
