rem /* DOS 32 bit - gcc 2.7.2.1 (djgpp v2)
rem  * a very simple make driver
rem  * Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
rem  */

@if "%KB_ECHO%"=="n" echo off

set EXTRA_CFLAGS=

set CC=gcc
set CFLAGS=@b/gcc.opt @b/dos32/dj2.opt %EXTRA_CFLAGS%
set MYLIB=libkb.a

echo Compiling, please be patient...
%CC% %CFLAGS% -c src/*.c
@if errorlevel 1 goto error
if exist %MYLIB% del %MYLIB%
ar rcs %MYLIB% @b/dos32/dj2.rsp
@if errorlevel 1 goto error

%CC% -s %CFLAGS% examples/kbtst.c %MYLIB% -o kbtst.exe
@if errorlevel 1 goto error
%CC% -s %CFLAGS% examples/keycodes.c %MYLIB% -o keycodes.exe
@if errorlevel 1 goto error
%CC% -s %CFLAGS% examples/simple.c %MYLIB% -o simple.exe
@if errorlevel 1 goto error
set CFLAGS=@b/gcc.opt @b/dos32/dj2.opt %EXTRA_CFLAGS% -Isrc
%CC% -s %CFLAGS% examples/tube.c %MYLIB% -lemu -o tube.exe
@if errorlevel 1 goto error
@goto done

%CC% -s %CFLAGS% examples/tube.c %MYLIB% -lemu -o tube_seal.exe @b/dos32/dj2_seal.opt
@if errorlevel 1 goto error
@goto done

%CC% -s %CFLAGS% examples/tube.c %MYLIB% -lemu -o tube_3d.exe @b/dos32/dj2_seal.opt @b/dos32/dj2_plsh.opt
@if errorlevel 1 goto error

:done
echo Done.
goto end
:error
echo error!
:end
