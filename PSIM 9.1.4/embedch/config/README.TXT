Copyright (c) 2001 SoftIntegration, Inc.

/***************** Configuration Files ************/
The following configuration files are located in this directory:

The following files are part of the CH language environment
chlogin         /* invoked by Ch automatically after chrc 
                   when Ch is used as login shell */
chrc            /* invoked by Ch automatically */ 
chrc.sample     /* same as chrc for backup */
chslogin        /* used by safe shell such as for network computing */
chsrc           /* used by safe shell such as for network computing */
chsrc.sample    /* same as  chsrc for backup */

In Unix, the following default sample files works 
if you put them under your home directory.
.chlogin        /* invoked by chlogin */ 
.chlogout       /* invoked at logout for login shell */
.chrc           /* included by chrc */     
.chslogin       /* invoked by chslogin */ 
.chslogout      /* invoked at logout for login shell */
.chsrc          /* included by chsrc */     
.mime.types     /* used by Web browser */
.mailcap        /* used by Web browser */

In Unix, the following files are for backup purpose.
.chsrc.sample   /* same as .chsrc for backup */
.chrc.sample    /* same as .chrc for backup */

In Windows, the following default sample files works 
if you put them under your home directory.
_chrc           /* included by chrc */     
_chsrc          /* included by chsrc */  

In windows, the following files are for backup purpose.
_chrc.sample    /* same as _chrc for backup */  
_chsrc.sample   /* same as _chsrc for backup */

/***************** Ch startup procedure  ************/
(1) In Unix

After initialization, Ch will execute 
CHHOME/config/chrc which includes ~/.chrc, if it exits.
With option -f for fast startup, file 
CHHOME/config/chrc and ~/.chrc are not executed.

If it is a login shell, 
after execution of CHHOME/config/chrc which includes ~/.chrc,
CHHOME/config/chlogin which includes ~/.chlogin, 
if it exists, will be executed.
Upon logout, 
file CHHOME/config/chlogout which includes ~/.chlogout,
if it exists, will be executed.

One can copy  CHHOME/config/.chrc to ~/.chrc
or run ch with option -d.
When ch is started with -d option,
it first checks if file ~/.chrc exists in user's
home directory. If not, Ch will copy CHHOME/config/.chrc to ~/.chrc.

(2)In Windows
Change dot '.' to '_' for startup files in Unix.
The login shell startup files  *login and *logout does not work
under Windows.

/***************** Safe Ch startup procedure  ************/
The startup procedure for safe Ch shell is the same as 
that for regular Ch shell, except that the startup files 
with prefix 'chs', instead of 'ch', will be used.
