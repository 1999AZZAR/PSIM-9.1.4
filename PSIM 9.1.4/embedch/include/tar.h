/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: tar.h
************************************************************/
#ifndef _TAR_H_
#define	_TAR_H_

#define TMAGIC        "ustar"         /* ustar and a null */
#define TMAGLEN       6
#define TVERSION      "00"            /* 00 and no null   */
#define TVERSLEN      2

/* Values used in typeflag field */
#define REGTYPE       '0'     /* Regular file  */
#define AREGTYPE      '\0'    /* Regular file  */
#define LNKTYPE       '1'     /* Link          */
#define SYMTYPE       '2'     /* Symbolic Link */
#define CHRTYPE       '3'     /* Char. special */
#define BLKTYPE       '4'     /* Block special */
#define DIRTYPE       '5'     /* Directory     */
#define FIFOTYPE      '6'     /* FIFO special  */
#define CONTTYPE      '7'     /* Reserved        */

/* Bits used in the mode field - values in octal */
#define TSUID         04000   /* Set UID on execution */
#define TSGID         02000   /* Set GID on execution */
#define TSVTX         01000   /* On directories, restricted deletion fla
g */

/* File permissions */
#define TUREAD        00400   /* read by owner        */
#define TUWRITE       00200   /* write by owner       */
#define TUEXEC        00100   /* execute/search owner */
#define TGREAD        00040   /* read by group        */
#define TGWRITE       00020   /* write by group       */
#define TGEXEC        00010   /* execute/search group */
#define TOREAD        00004   /* read by other        */
#define TOWRITE       00002   /* write by other       */
#define TOEXEC        00001   /* execute/search other */

#endif /* _TAR_H_ */
