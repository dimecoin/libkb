## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = no-dependencies


INCLUDES = -I$(top_srcdir)/include
CFLAGS = @CFLAGS@ @CFLAGS_O@ @CFLAGS_W@ @EXTRA_CFLAGS@


noinst_PROGRAMS = kbtst keycodes sigalrm simple tube

LDFLAGS = @LDFLAGS@ -static
LDADD = $(libkb)

kbtst_SOURCES = kbtst.c myconio.h intro.h
kbtst_LDADD   = $(LDADD) $(kbtst_LIBS)

tube_SOURCES  = tube.c tube_3d.h tube_gfx.h tube_snd.h
tube_LDADD    = $(LDADD) $(tube_LIBS)


tube.o: $(tube_SOURCES)

