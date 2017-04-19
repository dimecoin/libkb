/* intro.h -- include file used by 'libkb' test programs
 * Copyright (C) 1995-1998 Markus F.X.J. Oberhumer
 * For conditions of distribution and use, see copyright notice in kb.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the keyboard library and is
   subject to change. Applications should only use kb.h.
 */



#if defined(__KB_MSDOS)
#  include <io.h>
#  define KB_INSTALLED_MSG	"Keyboard interrupt installed."
#elif defined(__KB_LINUX)
#  include <unistd.h>
#  define KB_INSTALLED_MSG	"Keyboard handler installed."
#endif


/***********************************************************************
//
************************************************************************/

static char *_kb_compiler(char *s)
{
#if defined(__BORLANDC__)
	sprintf(s,"Borland C version 0x%x", __BORLANDC__);
#elif defined(__EMX__) && defined(__GNUC__)
	sprintf(s,"emx + gcc %s", __VERSION__);
#elif defined(__DJGPP__) && defined(__GNUC__)
	sprintf(s,"djgpp v2 + gcc %s", __VERSION__);
#elif defined(__GO32__) && defined(__GNUC__)
	sprintf(s,"djgpp v1 (go32) + gcc %s", __VERSION__);
#elif defined(_MSC_VER)
	sprintf(s,"Microsoft C version %d", _MSC_VER);
#elif defined(__TURBOC__)
	sprintf(s,"Turbo C version 0x%x", __TURBOC__);
#elif defined(__WATCOMC__)
	sprintf(s,"Watcom C version %d", __WATCOMC__);
#elif defined(__GNUC__) && defined(__VERSION__)
	int i = 0;
	char v[256];
	strcpy(v,__VERSION__);
	s[0] = 0;
#if defined(__linux__)
	strcpy(s,"Linux + ");
#endif
	while (i < 20 && v[i] && v[i] != ' ')
		i++;
	v[i] = 0;
	if (v[0] >= '0' && v[0] <= '9')
		strcat(s,"gcc-");
	strcat(s,v);
#else
	sprintf(s,"unknown compiler");
#endif

	sprintf(s+strlen(s),", %d bit", (int)(sizeof(int)*8));

	return s;
}


/***********************************************************************
//
************************************************************************/

static char *_kb_intro_text(char *s)
{
	sprintf(s,"libkb v%s test program  (", KB_VERSION_STRING);
	_kb_compiler(s+strlen(s));
	strcat(s,")");
	return s;
}


/*
vi:ts=4
*/
