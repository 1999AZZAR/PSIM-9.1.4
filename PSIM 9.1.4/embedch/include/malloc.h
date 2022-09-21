/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: malloc.h
************************************************************/
#ifndef _MALLOC_H_
#define _MALLOC_H_

#include<stddef.h>

extern void *malloc(size_t);
/* extern void free(void *); */
extern void *realloc(void *, size_t);
extern void *calloc(size_t, size_t);

#endif /* _MALLOC_H_ */
