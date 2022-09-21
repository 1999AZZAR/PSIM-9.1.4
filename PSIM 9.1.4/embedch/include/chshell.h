/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: chshell.h
************************************************************/
#ifndef _SHELL_H_
#define	_SHELL_H_

#include <stdio.h> /* for FILE in getline() */

/*
#define argc     _argc
#define argv     _argv
#define	cwd      _cwd
//#define debug _debug
#define	extc     _extc
#define	extf     _extf
#define	fpath    _fpath
#define	histsize _histsize
#define	home     _home
#define	host     _host
#define	ipath    _ipath
#define	path     _path
#define	prompt   _prompt
#define	shell    _shell
#define	status   _status
#define	term     _term
#define	user     _user
#define	warning  _warning
#define	stop     _stop
*/


/* return value for isvar() */
enum {
   CH_NOTVAR,
   CH_SYSTEMCONST,
   CH_SYSTEMVAR,
   CH_EXTERNVAR,
   CH_EXTERNFUN
};

struct chinfo_t {
   string_t  edition;        // "Professional", "Standard", or "Student"
   string_t releasedate;     // "March 17, 2005"
   string_t version;         // "", "Beta", or "Alpha"
   unsigned int vermajor;    // 5
   unsigned int verminor;    // 0
   unsigned int vermicro;    // 1
   unsigned int verbuild;    // 12201
};

extern int chinfo(chinfo_t *info);
extern int iskey(string_t name);
extern int isstudent(void);
extern int isvar(string_t name);
extern int sizeofelement(int etype);

#endif /* _SHELL_H_ */
