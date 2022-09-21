/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: setjmp.h
************************************************************/
#ifndef _SETJMP_H_
#define _SETJMP_H_

#define _JBLEN  4
typedef int jmp_buf[_JBLEN];
#define setjmp(env)  _setjmp(env)
#define longjmp(env, val) _longjmp(env, val)
/* void longjmp(jmp_buf env, int val); */

#endif  /* _SETJMP_H_ */  
