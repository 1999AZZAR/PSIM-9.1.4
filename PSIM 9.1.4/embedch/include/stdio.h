/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: stdio.h
: Note: standard I/O header file
************************************************************/
#ifndef _STDIO_H_
#define _STDIO_H_

#include <sys/va_list.h>

#define FILE           _FILE
#define FILENAME_MAX   _FILENAME_MAX
/* USE THIS IN THE FUTURE
#define FILENAME_MAX min(_FILENAME_MAX, 2047) 
*/
#define FOPEN_MAX      _FOPEN_MAX
#define	EOF            _EOF
/* for tmpnam() */
#define L_tmpnam       _L_tmpnam
#ifndef TMP_MAX
#define TMP_MAX        _TMP_MAX
#endif

/* for setvbuf() */
#define	BUFSIZ	       _BUFSIZ
#if defined(_LINUX_) || defined(_LINUXPPC_) || defined(_DARWIN_) || defined(_FREEBSD_) || defined(_QNX_)
#define _IOFBF 0 /* Fully buffered. */
#define _IOLBF 1 /* Line buffered. */
#define _IONBF 2 /* No buffering. */
#else
#define	_IOFBF		0000	/* full buffered */
#define	_IOLBF		0100	/* line buffered */
#define	_IONBF		0004	/* not buffered */
#define	_IOEOF 		0020	/* EOF reached on read */
#define	_IOERR 		0040	/* I/O error from system */
#define	_IOREAD 	0001	/* currently reading */
#define	_IOWRT 		0002	/* currently writing */
#define	_IORW 		0200	/* opened for reading and writing */
#define	_IOMYBUF 	0010	/* stdio malloc()'d buffer */
#endif

/* this is fixed in Ch 
#if defined(_WIN32_)
#define P_tmpdir        "/"         
#else
#define P_tmpdir        "/var/tmp/"
#endif
*/

/* for fseek() */
#define	SEEK_SET 	0
#define	SEEK_CUR 	1
#define	SEEK_END 	2

#define stdin _stdin
#define stdout _stdout
#define stderr _stderr

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
typedef unsigned long long size_t;  
#else
typedef unsigned int    size_t;      
#endif
#endif
typedef long    fpos_t;

#define getchar() getc(stdin)


extern restrict int	remove(const char *);
extern restrict int	rename(const char *, const char *);
extern FILE	*tmpfile(void);
extern char	*tmpnam(char *);
extern char	*tmpnam_r(char *);
extern char     *tempnam(const char *dir, const char *pfx);
extern int	fclose(FILE *);
extern int	fflush(FILE *);
extern restrict FILE	*fopen(const char *, const char *);
extern restrict FILE	*freopen(const char *, const char *, FILE *);
extern void	setbuf(FILE *, char *);
extern int	setvbuf(FILE *, char *, int, size_t);
extern int	fgetc(FILE *);
extern int	fputc(int, FILE *);
extern int	fputs(const char *, FILE *);
extern int	getc(FILE *);
extern int	putc(int, FILE *);
extern int	putchar(int);
extern int	puts(const char *);
extern int	ungetc(int, FILE *);
extern size_t	fwrite(const void *, size_t, size_t, FILE *);
extern int	fgetpos(FILE *, fpos_t *);
extern int	fseek(FILE *, long, int);
extern int	fsetpos(FILE *, const fpos_t *);
extern long	ftell(FILE *);
extern void	rewind(FILE *);
extern void	clearerr(FILE *);
extern int	feof(FILE *);
extern int	ferror(FILE *);
extern void	perror(const char *);
extern void	flockfile(FILE *);
extern void	funlockfile(FILE *);
extern int      getc_unlocked(FILE*stream);
extern int      putc_unlocked(int c, FILE*stream);
extern int      snprintf(char *s,  size_t n,  const  char  *format,  /*args*/ ...);
extern int      vsnprintf(char *s, size_t n, const char *format,  va_list ap);

/*
 * The following are known to POSIX and XOPEN, but not to ANSI-C.
 */

extern FILE	*fdopen(int, const char *);
extern char	*ctermid(char *);
extern int	fileno(FILE *);
extern int fprintf(FILE *stream,  const char *msg, ...);
extern int printf(const char *msg, ...);
extern int scanf(const char *msg, ...);


/*
 * The following are known to XOPEN, but not to ANSI-C or POSIX.
 */

extern restrict FILE	*popen(const char *, const char *);
extern char	*tempnam(const char *, const char *);
extern int	getw(FILE *);
extern int	putw(int, FILE *);
extern int	pclose(FILE *);

/* generic functions */
extern char *gets(char *s);
extern char *fgets(char *s, int n, FILE *stream);
extern size_t fread(void *ptr, size_t  size,  size_t  nitems,  FILE *stream);

/* these functions cannot be assigned to pointer to function
extern int	fprintf(FILE *, const char *, ...);
extern int	fscanf(FILE *, const char *, ...);
extern int	printf(const char *, ...);
extern int	scanf(const char *, ...);
extern int	sprintf(char *, const char *, ...);
extern int	sscanf(const char *, const char *, ...);
*/

/*
 * These functions are not supported in Ch for now
 */
/* vsscanf() vfscanf() vscanf() */


#if defined(_CHDLL_)
#include <chdl.h>
LOAD_CHDL(stdio)
#endif

#endif /* _STDIO_H_ */
