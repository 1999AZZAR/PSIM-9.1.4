/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: assert.h
************************************************************/
#ifndef _ASSERT_H_
#define _ASSERT_H_

void _assert(char *ex, char *file, int line) {
   printf("Assertion failed: %s, file %s, line %d\n",
             ex, file, line); 
   abort();
}
#endif	/* _ASSERT_H_ */

#undef  assert
#ifdef NDEBUG
#define assert(EX) ((void)0)
#else
#define assert(EX)  (void)((EX) || (_assert(#EX, __FILE__, __LINE__), 0))
#endif
 
