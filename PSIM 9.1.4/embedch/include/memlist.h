/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
#ifndef _MEMLIST_H_
#define _MEMLIST_H_
#include <stdlib.h>

struct chmemList { // for memory management
    struct chmemList *next;
    struct chmemList *previous;
    void     *object;
    int      type; // CH_MEMLIST_DEFAULT, CH_MEMLIST_CLASS, CH_MEMLIST_CLASS_ARRAY 
    int      num;  // num in new tag[num]
};

#define CH_MEMLIST_DEFAULT     0      // for malloc, calloc, realloc 
#define CH_MEMLIST_CLASS       0x1000 // by new tag
#define CH_MEMLIST_CLASS_ARRAY 0x2000 // by new tag[num]

#endif /* _MEMLIST_H_ */
