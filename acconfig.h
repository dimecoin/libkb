/* acconfig.h -- autoheader configuration file
 */


#ifndef __LIBKB_CONFIG_H
#define __LIBKB_CONFIG_H

/* $TOP$ */
@TOP@

/* acconfig.h

   Descriptive text for the C preprocessor macros that
   the distributed Autoconf macros can define.
   No software package will use all of them; autoheader copies the ones
   your configure.in uses into your configuration header file templates.

   The entries are in sort -df order: alphabetical, case insensitive,
   ignoring punctuation (such as underscores).  Although this order
   can split up related entries, it makes it easier to check whether
   a given entry is in the file.

   Leave the following blank line there!!  Autoheader needs it.  */


/* Define to your architecture name.  */
#undef MFX_ARCH

/* Define if your compiler is broken.  */
#undef MFX_PROG_CC_BUG_SIGNED_TO_UNSIGNED_CASTING

/* Define to your CPU name.  */
#undef MFX_CPU

/* Define if your memcmp is broken.  */
#undef NO_MEMCMP

/* Define to the name of the distribution.  */
#undef PACKAGE

/* Define to `long' if <stddef.h> doesn't define.  */
#undef ptrdiff_t

/* The number of bytes in a ptrdiff_t.  */
#undef SIZEOF_PTRDIFF_T

/* The number of bytes in a size_t.  */
#undef SIZEOF_SIZE_T

/* Define if you have the Plush 1.1.3 package.  */
#undef USE_PLUSH

/* Define if you have the Seal 1.03 package.  */
#undef USE_SEAL

/* Define to the version of the distribution.  */
#undef VERSION



/* Leave that blank line there!!  Autoheader needs it.
   If you're adding to this file, keep in mind:
   The entries are in sort -df order: alphabetical, case insensitive,
   ignoring punctuation (such as underscores).  */



@BOTTOM@

/* $BOTTOM$ */

#if defined(HAVE_SYS_RESOURCE_H) && !defined(TIME_WITH_SYS_TIME)
#  undef /**/ HAVE_SYS_RESOURCE_H
#endif

#if defined(HAVE_SYS_TIMES_H) && !defined(TIME_WITH_SYS_TIME)
#  undef /**/ HAVE_SYS_TIMES_H
#endif

#if defined(HAVE_ZLIB_H) && !defined(HAVE_LIBZ)
#  undef /**/ HAVE_ZLIB_H
#endif

#if (SIZEOF_PTRDIFF_T <= 0)
#  undef /**/ SIZEOF_PTRDIFF_T
#endif

#if (SIZEOF_SIZE_T <= 0)
#  undef /**/ SIZEOF_SIZE_T
#endif

#endif /* already included */

/*
vi:ts=4
*/
