## ---------------------------------------------------------- ##
## ANSIfy the C compiler and preprocessor whenever possible.  ##
## From Franc,ois Pinard and Markus Oberhumer.                ##
## ---------------------------------------------------------- ##

# serial 1

# @defmac mfx_PROG_CC_ANSI
# @maindex PROG_CC_ANSI
# @ovindex CC
# If the C compiler and preprocessor is not in ANSI C mode by default,
# try to add an option to output variable @code{CC} to make it so.
# This macro tries various options that select ANSI C on some system or another.
#
# Use this macro instead of @code{AM_PROG_CC_STDC} if your program
# is a real ANSI C program that cannot get un-ANSIfied. You also
# should use @code{AC_CONST}.
#
# If you use this macro, you should check after calling it whether the C
# compiler has been set to accept ANSI C; if not, the shell variable
# @code{mfx_cv_prog_cc_ansi} is set to @samp{no}.
# @end defmac

AC_DEFUN(mfx_PROG_CC_ANSI,
[AC_REQUIRE([AC_PROG_CC])
AC_BEFORE([$0], [AC_C_INLINE])
AC_BEFORE([$0], [AC_C_CONST])
dnl Force this before AC_PROG_CPP.  Some cpp's, eg on HPUX, require
dnl a magic option to avoid problems with ANSI preprocessor commands
dnl like #elif.
AC_BEFORE([$0], [AC_PROG_CPP])
AC_MSG_CHECKING(for ${CC-cc} option to accept ANSI C)
AC_CACHE_VAL(mfx_cv_prog_cc_ansi,
[mfx_cv_prog_cc_ansi=no
ac_save_CC="$CC"
# Don't try gcc -ansi; that turns off useful extensions and
# breaks some systems' header files.
# AIX                   -qlanglvl=ansi
# Ultrix and OSF/1      -std1
# HP-UX                 -Aa -D_HPUX_SOURCE
# HP-UX 10.20           -Ae
# SVR4                  -Xc -D__EXTENSIONS__
for ac_arg in "" -qlanglvl=ansi -std1 "-Aa -D_HPUX_SOURCE" "-Ae" "-Xc -D__EXTENSIONS__"
do
  CC="$ac_save_CC $ac_arg"
  AC_TRY_COMPILE(
[#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
# include <limits.h>  /* note the space */
#if 1 && !defined(UINT_MAX)
#  error "this is an error"
#  include "choke me"
#elif 0 || !defined(UINT_MAX)
#  error "this is an error"
#  include "choke me"
#elif !defined(UINT_MAX)
#  error "this is an error"
#  include "choke me"
#elif !(1-1)
/* ok */
#else
#  error "this is an error"
#  include "choke me"
#endif
#define STRINGIZE(x)        #x
#define MACRO_EXPAND(x)     STRINGIZE(x)
extern volatile signed char flag;
extern char *s ( void );
char *s ( void )
{
  static char n[] = MACRO_EXPAND(UINT_MAX);
  return flag ? n : n + 1;
}
/* Most of the following tests are stolen from RCS 5.7's src/conf.sh.  */
struct buf { int x; };
FILE * (*rcsopen) (struct buf *, struct stat *, int);
static char *e (p, i)
     char **p;
     int i;
{
  return p[i];
}
static char *f (char * (*g) (char **, int), char **p, ...)
{
  char *s;
  va_list v;
  va_start (v,p);
  s = g (p, va_arg (v,int));
  va_end (v);
  return s;
}
int test (int i, double x);
struct s1 {int (*f) (int a);};
struct s2 {int (*f) (double a);};
int pairnames (int, char **, FILE *(*)(struct buf *, struct stat *, int), int, int);
int argc;
char **argv;
], [
return f (e, argv, 0) != argv[0]  ||  f (e, argv, 1) != argv[1];
],
[mfx_cv_prog_cc_ansi="$ac_arg"; break])
done
CC="$ac_save_CC"
])
if test -z "$mfx_cv_prog_cc_ansi"; then
  AC_MSG_RESULT([none needed])
else
  AC_MSG_RESULT($mfx_cv_prog_cc_ansi)
fi
case "x$mfx_cv_prog_cc_ansi" in
  x|xno) ;;
  *) CC="$CC $mfx_cv_prog_cc_ansi" ;;
esac
])
