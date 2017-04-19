/* tube.c -- test program for libkb with graphic and sound libraries
 * Copyright (C) Markus F.X.J. Oberhumer and James Johnson
 * For conditions of distribution and use, see copyright notice in kb.h
 */


/* note: There is not much keyboard action in this program.
 *       This is mainly a demonstration of the safety features of
 *       libkb when allocating hardware resources.
 */


/* note: I've completely rewritten this program, original info follows */

/*************************************************************************
	Program	: Tubular
	File	: tube.cpp

	Programmer	: James Johnson <plexus@stein.u.washington.edu>
	Date		: 1-14-94
	Version		: 1.0
 ************************************************************************/


#if 0 && defined(__EMX__)
#  include <sys/emx.h>
#endif
#if defined(LIBKB_HAVE_CONFIG_H)
#  include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <kb.h>
#if defined(__KB_MSDOS)
#  include "_kb.h"					/* KB_INT86, KB_INP8, KB_OUTP8 */
#endif
#include "intro.h"

#if defined(__KB_LINUX)
#  define stricmp	strcasecmp
#endif

#if !defined(__inline__) && !defined(__GNUC__)
#  if defined(__cplusplus)
#    define __inline__		inline
#  else
#    define __inline__		/* nothing */
#  endif
#endif


static int in_graphics = 0;
static int in_sound = 0;
static int in_3d = 0;

static int wait_for_vsync = 1;

static int is_win = -1;


#include "tube_snd.h"
#include "tube_gfx.h"
#include "tube_3d.h"
#ifdef HAVE_3D
#  ifndef USE_DOUBLE_BUFFER
#    define USE_DOUBLE_BUFFER
#  endif
#endif

#if 0 && !defined(USE_DOUBLE_BUFFER)
#  define USE_DOUBLE_BUFFER
#endif


/***********************************************************************
//
************************************************************************/

#if defined(USE_DOUBLE_BUFFER)

static unsigned char *screen = NULL;

#define setpixel(x,y,c)		screen[(x)+(y)*WIDTH] = (unsigned char)(c);
#define clearpixel(x,y)		((void)0)

#else

#define clearpixel(x,y)		setpixel(x,y,0)

#endif


/***********************************************************************
// Standalone BogoMips program v1.3 by Jeff Tranter
//
// Based on code Linux kernel code in init/main.c and
// include/linux/delay.h
//
// For more information on interpreting the results,
// see the BogoMIPS Mini-HOWTO document.
************************************************************************/

/* portable version */
static void bogo_delay(long loops)
{
	long i;
	for (i = loops; i >= 0 ; i--)
		;
}


/* return 33.55 BogoMips as 3355 */
long bogomips(long min_interval_msec)
{
	clock_t ticks, min_ticks;
	unsigned long loops_per_sec = 1;

	if (min_interval_msec < 10)		/* at least 10 millisecs */
		min_interval_msec = 10;

	min_ticks = (min_interval_msec * (long)(CLOCKS_PER_SEC)) / 1000;
	if (min_ticks < 2)
		min_ticks = 2;

	while ((loops_per_sec <<= 1) != 0)
	{
		ticks = clock();
		bogo_delay(loops_per_sec);
		ticks = clock() - ticks;
		if (ticks >= min_ticks)
	  		return ((loops_per_sec / ticks) * (long)(CLOCKS_PER_SEC)) / 5000;
	}
	return -1;
}


long print_bogomips(FILE *f, long min_interval_msec)
{
	long bm;

	fprintf(f,"Calibrating delay loop.. ");
	fflush(f);
	bm = bogomips(min_interval_msec);
	if (bm <= 0)
		fprintf(f,"failed\n");
	else
		fprintf(f,"ok - %lu.%02lu BogoMips\n", bm / 100, bm % 100);
	fflush(f);
	return bm;
}


/***********************************************************************
//
************************************************************************/

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

#define Min_Z        (1  << 3)				/* color  1 */
#define Max_Z       ((64 << 3) - 1)			/* color 63 */
#define Min_Dz      1
#define Max_Dz      64
#define Def_DZ		3
#define Step	    20
#define Max_Rand	256
#define Max_Active	((Max_Z / 2) * Step)

typedef struct
{
	int x;
	int y;
	int z;
	int Old_x;
	int Old_y;
	int xc;
	int yc;
}
Star;

#if defined(__KB_MSDOS16)
#define PStar	Star __huge *
static Star __huge star[Max_Active];
#else
typedef Star *PStar;
static Star star[Max_Active];
#endif

static int Xtable[Max_Rand];
static int Ytable[Max_Rand];
static int Index[Max_Rand];


/* setup colors - lowest z value is nearest star (should be brightest) */
/* play around - this really changes the way it looks */
/* colors 64-255 are not used, so you can still add plenty of stuff */

static const unsigned char pal[64*3] = {
 0, 0,15, 59,59,59, 54,54,54, 49,49,49, 45,45,45, 41,41,41, 38,38,38, 35,35,35,
32,32,32, 29,29,29, 27,27,27, 25,25,25, 23,23,23, 21,21,21, 19,19,19, 17,17,17,
16,16,16, 15,15,15, 13,13,15, 12,12,15, 11,11,15, 10,10,15, 10,10,15,  9, 9,15,
 8, 8,15,  7, 7,15,  7, 7,15,  6, 6,15,  6, 6,15,  5, 5,15,  5, 5,15,  4, 4,15,
 4, 4,15,  4, 4,15,  3, 3,15,  3, 3,15,  3, 3,15,  3, 3,15,  2, 2,15,  2, 2,15,
 2, 2,15,  2, 2,15,  2, 2,15,  2, 2,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,
 1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,
 1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15,  1, 1,15
};

void init_pal(void)
{
#if 1
	/* use pre-computed pal to (avoid linking the math library ?) */
	int i;
	const unsigned char *p = pal;
	for (i = 0; i < 64; i++, p += 3)
		setcolor(i,p[0],p[1],p[2]);
#else
	int i;
	setcolor(0,0,0,15);
	for (i = 1; i < 64; i++)
	{
#if 1
		int tmp = (int) (pow(64.0,(48-i)/48.0) + 0.5);
		if (tmp > 63)
			tmp = 63;
		else if (tmp < 1)
			tmp = 1;
#else
		unsigned tmp = (unsigned) (pow(64,i/48.0) + 0.5);
		tmp = (tmp > 63) ? 63 : tmp;
		tmp = 63 - tmp;
#endif
		setcolor(i, tmp, tmp, (tmp < 15) ? 15 : tmp);
	}
#endif
}


/***********************************************************************
// init and draw the tube
************************************************************************/

static void init(void)
{
	int i, k, tmp;
	unsigned Randnum;

	for (i = 0; i < Max_Active; i++)
		star[i].z = 0;

	for (i = 0; i < Max_Rand; i++)
	{
		Xtable[i] = (int)(128.0 * cos(i * 2*M_PI / Max_Rand) + 0.5);
		Ytable[i] = (int)(128.0 * sin(i * 2*M_PI / Max_Rand) + 0.5);
		Index[i] = i;
	}

	/* shuffle Index[] */
	for (k = 0; k < Max_Rand/2; k++)
		for (i = 0; i < Max_Rand; i++)
		{
			Randnum = rand() % Max_Rand;
			tmp = Index[Randnum];
			Index[Randnum] = Index[i];
			Index[i] = tmp;
		}
}


static unsigned long doit(void)
{
	int i, k;
	int dz				= Def_DZ;
	unsigned Tube_Xr	= 60;
	unsigned Tube_Yr	= 60;
	unsigned X_choice	= 0;
	unsigned Y_choice	= 0;
	unsigned X_count	= 64;
	unsigned Y_count	= 0;
	unsigned D_tube_xr	= 64;
	unsigned D_tube_yr	= 0;
	int Num_Active		= 0;
	int First_Free      = 0;
	unsigned count		= 0;
	unsigned long frames = 0;

	for (;;)
	{
#if defined(USE_DOUBLE_BUFFER)
		memset(screen,0,WIDTH*HEIGHT);
#endif

	/* fill in new stars */
		i = First_Free;
		for (k = 0; k < Step && Num_Active < Max_Active; k++)
		{
			while (star[i].z != 0)
				i++;
			star[i].x = Tube_Xr * Xtable[Index[X_choice]];
			star[i].y = Tube_Yr * Ytable[Index[Y_choice]];
			star[i].z = Max_Z;
			star[i].xc = WIDTH/2  + (120 * Xtable[X_count]) / Max_Rand;
			star[i].yc = HEIGHT/2 + ( 80 * Ytable[Y_count]) / Max_Rand;

			if (++X_choice >= Max_Rand)
				X_choice = 0;
			if (++Y_choice >= Max_Rand)
				Y_choice = 0;

			Num_Active++;
			i++;
		}

	/* move stars */
#if defined(__DJGPP__) && !defined(USE_ALLEGRO)
		_farsetsel(_dos_ds);	/* set selector for VIDMEM */
#endif
		for (i = 0; i < Max_Active; i++)
		{
			PStar s = &star[i];

			if (s->z == 0)	/* star is not active */
				continue;

 			if (s->z > Min_Z)
			{
				/* calculate the new one */
				int X_tmp = s->x / s->z + s->xc;

				/* if x lies within boundaries */
				if (X_tmp >= 0 && X_tmp < (int)WIDTH)
				{
					int Y_tmp = s->y / s->z + s->yc;

					/* if y lies within boundaries.*/
					if (Y_tmp >= 0 && Y_tmp < (int)HEIGHT)
					{
						if (X_tmp != s->Old_x || Y_tmp != s->Old_y)
						{
							/* erase the old star */
							clearpixel(s->Old_x,s->Old_y);
							/* draw new star */
							s->Old_x = X_tmp;
							s->Old_y = Y_tmp;
							setpixel(X_tmp,Y_tmp,s->z >> 3);
						}
						s->z -= dz;

						continue;		/* <- done */
					}
				}
			}

			/* erase the old star */
			clearpixel(s->Old_x,s->Old_y);

			/* remove the star */
			s->z = 0;
			Num_Active--;
			if (i < First_Free)
				First_Free = i;
		}

#if defined(HAVE_3D)
#if defined(HAVE_SOUND)
		if (in_sound && mod)
			snd_update();
#endif
		render_3d();
#endif

		X_count += 2;
		if (X_count >= Max_Rand) X_count = 0;
		Y_count++;
		if (Y_count >= Max_Rand) Y_count = 0;

	/* this section increases the X and Y radii, giving ellipses */
		if (++count >= 5)
		{
			count = 0;
			Tube_Xr = 20 * Xtable[D_tube_xr] / Max_Rand + 60;
			Tube_Yr = 20 * Ytable[D_tube_yr] / Max_Rand + 60;
			if(++D_tube_xr >= Max_Rand) D_tube_xr = 0;
			if(++D_tube_yr >= Max_Rand) D_tube_yr = 0;
		}

		frames++;

	/* handle keys */
		if (kb_mode() && (kb_key(KB_SCAN_ESC) || kb_key(KB_SCAN_Q)))
			return frames;

		while (kb_kbhit())
		{
			int Factor;
			unsigned key;

			Factor = dz >= 10 ? 2 : 1;
			key = kb_getkey();
			switch(key)
			{
			case 0x1b:		/* Esc */
			case 'q':
			case 'Q':
				return frames;
			case '+':
			case 'f':
			case 'F':
				if (dz+Factor <= Max_Dz) dz += Factor;
				break;
			case '-':
			case 's':
			case 'S':
				if (dz-Factor >= Min_Dz) dz -= Factor;
				break;

			/* a little MOD-player :-) */
#if defined(USE_SEAL)
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if (in_sound && mod)
				{
					key -= '0';
					ASetModuleVolume(key * 7);
				}
				break;

			case 0x247:		/* Home */
			case 0x24b:		/* cursor left */
			case 0x24d:		/* cursor right */
				if (in_sound && mod)
				{
					UINT order, row;
					if (AGetModulePosition(&order,&row) != 0)
						break;
					if (key == 0x24b && order > 0)
						order--;
					else if (key == 0x24d)
						order++;
					else if (key == 0x247)
						order = 0;
					row = 0;
					if (order < mod->nOrders)
						ASetModulePosition(order,row);
				}
				break;
#endif
			}
		}

#if defined(HAVE_SOUND)
		if (in_sound && mod)
			snd_update();
#endif

		/* wait for vertical retrace */
		if (wait_for_vsync)
			waitvrt();

#if defined(USE_DOUBLE_BUFFER)
		/* draw on screen */
		blit_screen(screen);
#endif
	}
}


/***********************************************************************
// cleanup - you should deallocate resources in the reverse order
// you allocated them and prepare for the fact that the cleanup-function
// can be called more than once
************************************************************************/

void my_cleanup(void)
{
	kb_remove();
	exit_gfx();
	exit_snd();
}

void my_emergency_cleanup(void)
{
	kb_remove();
	exit_gfx();
	exit_snd();
}


/***********************************************************************
//
************************************************************************/

static void usage(void)
{
	exit(1);
}


/***********************************************************************
//
************************************************************************/

int main(int argc, char *argv[])
{
	int i;
	unsigned long frames;
	clock_t t1, t2;
	double secs, fps;
	char s[160+1];
	const char *argv0 = "tube";

	unsigned long kflags = KB_FLAG_EMERGENCY_EXIT | KB_FLAG_EMERGENCY_SIGALRM;
	int mode = 0;
	int use_kb = 1;
	int use_sound = -1;
	char modfile[511] = { 0 };
	unsigned sample_rate;
	long bm;

	atexit(my_cleanup);

	fputs("\n",stdout);
	fputs(_kb_intro_text(s),stdout);
	fputs("\n\n",stdout);
	is_win = _kb_iswin();
	if (is_win > 0)
		printf("I am running in a Windows %d.%02d DOS box.\n",
				is_win / 256, is_win % 256);

	/* check CPU speed to get default sample rate */
	bm = print_bogomips(stdout,500);
	if (bm < 1000)
		sample_rate = 11025 / 2;
	else if (bm < 1500)
		sample_rate = 11025;
	else if (bm > 4500)
		sample_rate = 44100u;
	else
		sample_rate = 22050;
	printf("\n");


	/* handle options */
	for (i = 1; i < argc && argv[i][0] == '-'; i++)
	{
		const char *p = &argv[i][1];

		if (isdigit(*p))
			mode = atoi(p);
		else if (*p == 'f' && isdigit(p[1]) && isdigit(p[2]) && isdigit(p[3]))
			sample_rate = atoi(p+1);
		else if (stricmp(p,"-no-kb") == 0)
			use_kb = 0;
		else if (stricmp(p,"-no-atexit") == 0)
			kflags |= KB_FLAG_NO_ATEXIT;
		else if (stricmp(p,"-no-signal") == 0)
			kflags |= KB_FLAG_NO_SIGNAL;
		else if (stricmp(p,"-no-sound") == 0)
			use_sound = 0;
		else if (stricmp(p,"-no-vsync") == 0)
			wait_for_vsync = 0;
		else if (stricmp(p,"-sound") == 0)
			use_sound = 1;
		else if (stricmp(p,"-vsync") == 0)
			wait_for_vsync = 1;
		else
		{
			fprintf(stderr,"%s: invalid option '%s'\n",argv0,argv[i]);
			usage();
		}
	}

	/* handle arguments */
	if (i < argc)
		strcpy(modfile,argv[i++]);

	if (wait_for_vsync < 0)
	{
		if (bm > 4000)
			wait_for_vsync = 1;
		else if (use_sound && bm > 2800)
			wait_for_vsync = 1;
		else
			wait_for_vsync = 0;
	}
	if (wait_for_vsync)
		printf("%s: vsync enabled\n",argv0);
#if defined(USE_DOUBLE_BUFFER)
	printf("%s: double-buffer enabled\n",argv0);
#endif
	fflush(stdout); fflush(stderr);

	/* init sound */
#if defined(HAVE_SOUND)
	if (sample_rate < 5000)
		sample_rate = 5000;
	else if (sample_rate > 44100u)
		sample_rate = 44100u;
	if (use_sound && bm < 800)		/* less than 8.00 */
	{
		use_sound = 0;
		printf("%s: your machine is too slow, sound disabled\n",argv0);
	}
	if (use_sound && modfile[0] == 0)
	{
		const char *p = "tube.mod";
		int b;
		FILE *f;

		/* get basename */
		const char *n, *nn;
		for (nn = n = argv[0]; *nn; nn++)
			if (*nn == '/' || *nn == '\\' || *nn == ':')
				n = nn + 1;
		b = (int) (n - argv[0]);
		strcpy(modfile,p);
		f = fopen(modfile,"rb");
		if (f == NULL && b > 0)
		{
			memcpy(modfile,argv[0],b);
			strcpy(modfile+b,p);
			f = fopen(modfile,"rb");
		}
		if (f == NULL && b > 0)
		{
			memcpy(modfile,argv[0],b);
			strcpy(modfile+b,"../");
			strcat(modfile,p);
			f = fopen(modfile,"rb");
		}
		if (f != NULL)
			fclose(f);
		else
			modfile[0] = 0;
	}
	if (use_sound && modfile[0] && snd_init(modfile,sample_rate) == 0)
	{
		printf("%s: sound system initialized\n",argv0);
		fflush(stdout);
		fflush(stderr);
		in_sound = 1;
	}
#endif /* HAVE_SOUND */

	/* print instructions and wait for a key */
	printf("\nInstructions:\n");
	printf("    Esc, q ... quit\n");
	printf("    +, f   ... faster\n");
	printf("    -, s   ... slower\n");
#ifdef USE_SEAL
	if (in_sound)
		printf("    0..9   ... sound volume\n");
#endif
	printf("    LControl-RControl-C or LControl-RMenu-C to test emergency exit\n");
	if (isatty(fileno(stdout)) && isatty(fileno(stdin)))
	{
		printf("\n%s: hit any key to start...\n",argv0);
		fflush(stdout); fflush(stderr);
		kb_os_waitkey();
	}

	/* init graphics */
	if (mode < 0)				/* allow '-1' */
		mode = -mode;
#if defined(USE_DOUBLE_BUFFER)
	mode = 0;
#endif
	if (init_gfx(mode) != 0)
	{
		printf("tube: could not enter graphics mode\n");
		exit(1);
	}
	in_graphics = 1;
	init_pal();

	/* init keyboard after graphics (svgalib) */
	if (use_kb)
	{
		if (kb_install(kflags) == 0)
		{
			kb_set_cleanup(NULL,my_cleanup);
			kb_set_emergency_cleanup(NULL,my_emergency_cleanup);
#if 1 && defined(__KB_MSDOS) && defined(USE_ALLEGRO)
			three_finger_flag = 0;
			kb_handler_callback = simulate_keyint;
#endif
		}
	}

#if defined(USE_DOUBLE_BUFFER)
	if (screen == NULL)
		screen = malloc(WIDTH*HEIGHT);
	if (screen == NULL)
		exit(1);
#endif
#if defined(HAVE_3D)
	init_3d(screen);
#endif

	srand(0);
	srand((unsigned)time(NULL));
	init();
	t1 = clock();
	frames = doit();
	t2 = clock();

#if defined(USE_DOUBLE_BUFFER)
	free(screen);
#endif

#if 0
	/* now let's test the libkb signal handler.
	 * !!! DON'T TRY THIS WITH Borland C v3.1, see documentation !!!
	 * (works with Borland C v4.0, though)
	 */
#if !(defined(__KB_MSDOS16) && defined(__BORLANDC__))
	if (kb_mode() && (kb_flags() & KB_FLAG_SIGNAL_DONE))
		assert(0 == 1);
#endif
#endif

#if 0
	/* another test of the libkb signal handler */
	if (kb_mode() && (kb_flags() & KB_FLAG_SIGNAL_DONE))
	{
		volatile int a = 0;
		frames += 10 / a;
	}
#endif


	my_cleanup();

	fputs("\n",stdout);
	fputs(_kb_intro_text(s),stdout);
	fputs("\n\n",stdout);
	printf("Please send your bug reports, fixes, enhancements or suggestions to:\n");
	printf("Markus F.X.J. Oberhumer <markus.oberhumer@jk.uni-linz.ac.at>\n");
	printf("\n");


	secs = ((double)t2-(double)t1) / (CLOCKS_PER_SEC);
	fps = (secs > 0.001) ? frames / secs : 0;
	printf("%lu frames, %.2f secs, %.2f frames/sec\n", frames, secs, fps);

	printf("\nCredits:\n");
	printf("  James Johnson <plexus@stein.u.washington.edu>\n");
#ifdef USE_SEAL
	printf("  Carlos Hasan <chasan@dcc.uchile.cl> - SEAL audio library\n");
#endif
#ifdef USE_PLUSH
	printf("  Justin Frankel <justin@nullsoft.com> - Plush 3D library\n");
#endif
	fputs("\n",stdout);

	sample_rate = sample_rate;
	return 0;
}


/*
vi:ts=4
*/

