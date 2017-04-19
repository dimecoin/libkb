## Process this file with automake to create Makefile.in
#
# Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
#

AUTOMAKE_OPTIONS = no-dependencies


### LIBKB_CFLAGS = -DKB_DEBUG=1

INCLUDES = -I$(top_srcdir)/include
CFLAGS = @CFLAGS@ @CFLAGS_O@ @CFLAGS_W@ @EXTRA_CFLAGS@ $(LIBKB_CFLAGS)


EXTRA_DIST = mkkbname.pl
## BUILT_SOURCES = _kbname.hh _kbtable.hh

noinst_PROGRAMS = mktables


lib_LTLIBRARIES = libkb.la

libkb_la_LDFLAGS = -version-info 1:0:1

libkb_la_SOURCES = \
    kbhandle.c kblinux.c kbmlock.c kbos.c kbsignal.c kbtables.c \
     _kbname.hh _kbtable.hh \
      _handler.h _kb.h _kblinux.h _kbmsdos.h


if GMAKE
if MAINTAINER

kbtables.lo: _kbname.hh _kbtable.hh

_kbname.hh: mkkbname.pl $(top_srcdir)/include/kb.h
	perl -w $^ > $@

_kbtable.hh: mktables
	./$< > $@

endif
endif


