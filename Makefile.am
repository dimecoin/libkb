## Process this file with automake to produce Makefile.in
#
# Copyright (C) 1996-1998 Markus F.X.J. Oberhumer
#

AUTOMAKE_OPTIONS = 1.3 foreign no-dependencies

SUBDIRS = include src examples util

ACLOCAL_AMFLAGS = -I acconfig/m4


INCLUDES = -I$(top_srcdir)/include
CFLAGS = @CFLAGS@ @CFLAGS_O@ @CFLAGS_W@


EXTRA_DIST = \
    COPYING.KB DESC.SDI FILE_ID.DIZ README.1ST libkb.lsm


dist-hook:
	cp -rpi $(srcdir)/acconfig $(srcdir)/b $(srcdir)/doc $(distdir)/
	-cp -rpi $(srcdir)/bin $(distdir)/

