/* tube_gfx.h -- graphics wrapper
 * Copyright (C) 1996-1998 Markus F.X.J. Oberhumer
 * For conditions of distribution and use, see copyright notice in kb.h
 */


/***********************************************************************
// Linux svgalib wrapper
************************************************************************/

#if defined(__KB_LINUX)

#include <vga.h>
#include <vgagl.h>

static GraphicsContext physical_screen;

int init_gfx(int mode)
{
	static const int modes[] =
		{ G320x200x256, G320x240x256, G720x348x2, G640x480x256 };
	int m;

	if (mode < 0 || mode > 3)
		mode = 0;
	m = modes[mode];

	vga_init();
	if (vga_setmode(m) != 0)		/* <- this does the real init of svgalib */
		return -1;
	if (gl_setcontextvga(m) != 0)
		return -1;
	gl_getcontext(&physical_screen);
	/* gl_enableclipping(); */		/* not needed */
	return 0;
}

void setmode03(void)
{
	vga_setmode(TEXT);
}

void setcolor(int c, int r, int g, int b)
{
	vga_setpalette(c,r,g,b);
}

__inline__ void setpixel(int x, int y, int c)
{
	vga_setcolor(c);
	vga_drawpixel(x,y);
}

void waitvrt(void)
{
	vga_waitretrace();
}

void blit_screen(const void *screen)
{
	memcpy(VBUF,screen,WIDTH*HEIGHT);
}

#endif


/***********************************************************************
// Allegro graphics wrapper (MSDOS)
************************************************************************/

#if defined(USE_ALLEGRO)

#include <allegro.h>

#define WIDTH	SCREEN_W
#define HEIGHT	SCREEN_H

void setcolor(int c, int r, int g, int b)
{
	RGB rgb;

	rgb.r = r; rgb.g = g; rgb.b = b;
	set_color(c, &rgb);
}

int init_gfx(int mode)
{
	int c, w, h;
	c = GFX_AUTODETECT; w = 320; h = 200;

	UNUSED(mode);

	allegro_init();
	if (is_win == 0)
		install_mouse();
	install_timer();
	install_keyboard();
	/* initialise_joystick(); */

	if (set_gfx_mode(GFX_VGA, 320, 200, 0, 0) != 0)
	{
		allegro_exit();
		printf("Allegro: error setting graphics mode\n%s\n\n", allegro_error);
		return -1;
	}

	if (is_win == 0)
	{
		/* colors gfx_mode_select() */
		setcolor(0, 0,0,0);
		setcolor(1, 48,48,48);
		setcolor(2, 56,10,10);
		/* colors for mouse cursor */
		setcolor(16, 0,0,0);
		setcolor(255, 63,63,63);
		clear(screen);
		textout_centre(screen,font,"Allegro Setup",SCREEN_W/2,10,2);
		gui_fg_color = 0;
		gui_bg_color = 1;
		if (!gfx_mode_select(&c, &w, &h))
		{
			allegro_exit();
			return -1;
		}
		if (set_gfx_mode(c, w, h, 0, 0) != 0)
		{
			allegro_exit();
			printf("Allegro: error setting graphics mode\n%s\n\n", allegro_error);
			return -1;
		}
	}

	remove_keyboard();
	clear(screen);
	set_clip(screen,0,0,0,0);	/* clipping not needed */
	return 0;
}

void setmode03(void)
{
	allegro_exit();
}

__inline__ void setpixel(int x, int y, int c)
{
	putpixel(screen,x,y,c);
}

void waitvrt(void)
{
	vsync();
}

#endif /* USE_ALLEGRO */


/***********************************************************************
// MSDOS mode 13h graphics wrapper
************************************************************************/

#if defined(__KB_MSDOS) && !defined(USE_ALLEGRO)

#define WIDTH	320u
#define HEIGHT	200u

static int old_mode = 3;

#if defined(__KB_MSDOS16) && defined(__BORLANDC__)
#  define VIDMEM	((unsigned char far *) 0xa0000000l)
#elif defined(__KB_MSDOS16) && defined(_MSC_VER)
#  define VIDMEM	((unsigned char __far *) 0xa0000000l)
#elif defined(__DJGPP__)
#  include <sys/farptr.h>
#  include <sys/movedata.h>
#  define VIDMEM	0xa0000
#elif defined(__GO32__)
#  define VIDMEM	((unsigned char *) 0xd0000000)
#elif defined(__EMX__)
   static unsigned char *VIDMEM = NULL;
#elif defined(__WATCOMC__)
#  define VIDMEM	((unsigned char *) 0xa0000)
#endif


#if defined(KB_INT86)
int init_gfx(int mode)
{
	KB_INT86_REGS regs;

	UNUSED(mode);

#if defined(__EMX__)
	if (!KB_USE_INT86())
		return -1;			/* _int86() not allowed */
	if (_portaccess(0x3c8, 0x3da) != 0)
		return -1;
	if (VIDMEM == NULL)
		VIDMEM = _memaccess(0xa0000, 0xaffff, 1);
	if (VIDMEM == NULL)
		return -1;
#endif
	_kb_int86_regs_init_ax(&regs,0x0f00);
	KB_INT86(0x10,&regs);
	old_mode = regs.h.al & 0x7f;
	_kb_int86_regs_init_ax(&regs,0x13);
	KB_INT86(0x10,&regs);
	return 0;
}

void setmode03(void)
{
	KB_INT86_REGS regs;

#if defined(__EMX__)
	if (!KB_USE_INT86())
		return;				/* _int86() not allowed */
#endif
	_kb_int86_regs_init_ax(&regs,old_mode);
	KB_INT86(0x10,&regs);
}
#endif


__inline__ void setpixel(int x, int y, int c)
{
#if defined(__DJGPP__)
	_farnspokeb(VIDMEM + y*WIDTH + x, c);
#else
	*(VIDMEM + y*WIDTH + x) = c;
#endif
}


void blit_screen(const void *screen)
{
#if defined(__DJGPP__)
	_dosmemputl(screen,WIDTH*HEIGHT/4,VIDMEM);
#else
	memcpy(VIDMEM,screen,WIDTH*HEIGHT);
#endif
}


void setcolor(int c, int r, int g, int b)
{
	/* fprintf(stderr,"%3d %3d %3d %3d\n",c,r,g,b); */
	KB_OUTP8(0x3c8, c);
	_kb_usleep(5);
	KB_OUTP8(0x3c9, r);
	_kb_usleep(5);
	KB_OUTP8(0x3c9, g);
	_kb_usleep(5);
	KB_OUTP8(0x3c9, b);
	_kb_usleep(5);
}


/* wait for the vertical retrace trailing edge */
void waitvrt(void)
{
	while (!(KB_INP8(0x3da) & 0x8))		/* wait for retrace to end */
		;
	while ((KB_INP8(0x3da) & 0x8))		/* wait for retrace to start again */
		;
}


#endif /* __KB_MSDOS */


/***********************************************************************
//
************************************************************************/

void exit_gfx(void)
{
	if (in_graphics)
	{
		in_graphics = 0;
		setmode03();
	}
	/* _kb_port_debug(); */
}


/*
vi:ts=4
*/

