/* config.h.  Generated automatically by configure.  */
/* config.hin.  Generated automatically from configure.in by autoheader.  */
/* acconfig.h -- autoheader configuration file
 */


#ifndef __LIBKB_CONFIG_H
#define __LIBKB_CONFIG_H

/* $TOP$ */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define if your C compiler doesn't accept -c and -o together.  */
/* #undef NO_MINUS_C_MINUS_O */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#define TIME_WITH_SYS_TIME 1

/* Define to your architecture name.  */
#define MFX_ARCH "i386"

/* Define to your CPU name.  */
#define MFX_CPU "i686"

/* Define if your memcmp is broken.  */
/* #undef NO_MEMCMP */

/* Define to the name of the distribution.  */
#define PACKAGE "libkb"

/* Define if you have the Seal 1.03 package.  */
/* #undef USE_SEAL */

/* Define to the version of the distribution.  */
#define VERSION "1.01"

/* Define if you have the memcmp function.  */
#define HAVE_MEMCMP 1

/* Define if you have the memcpy function.  */
#define HAVE_MEMCPY 1

/* Define if you have the memmove function.  */
#define HAVE_MEMMOVE 1

/* Define if you have the memset function.  */
#define HAVE_MEMSET 1

/* Define if you have the <assert.h> header file.  */
#define HAVE_ASSERT_H 1

/* Define if you have the <audio.h> header file.  */
/* #undef HAVE_AUDIO_H */

/* Define if you have the <ctype.h> header file.  */
#define HAVE_CTYPE_H 1

/* Define if you have the <curses.h> header file.  */
#define HAVE_CURSES_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <ncurses.h> header file.  */
#define HAVE_NCURSES_H 1

/* Define if you have the <plush.h> header file.  */
/* #undef HAVE_PLUSH_H */

/* Define if you have the <stddef.h> header file.  */
#define HAVE_STDDEF_H 1

/* Define if you have the <time.h> header file.  */
#define HAVE_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <vga.h> header file.  */
/* #undef HAVE_VGA_H */

/* Define if you have the <vgagl.h> header file.  */
/* #undef HAVE_VGAGL_H */

/* Define if you have the <vgakeyboard.h> header file.  */
/* #undef HAVE_VGAKEYBOARD_H */

/* Define if you have the <vgamouse.h> header file.  */
/* #undef HAVE_VGAMOUSE_H */

/* Define if you have the audio library (-laudio).  */
/* #undef HAVE_LIBAUDIO */

/* Define if you have the curses library (-lcurses).  */
/* #undef HAVE_LIBCURSES */

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* Define if you have the ncurses library (-lncurses).  */
#define HAVE_LIBNCURSES 1

/* Define if you have the vga library (-lvga).  */
/* #undef HAVE_LIBVGA */

/* Define if you have the vgagl library (-lvgagl).  */
/* #undef HAVE_LIBVGAGL */

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
