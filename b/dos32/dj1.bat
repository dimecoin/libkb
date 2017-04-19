rem /* DOS 32 bit - gcc 2.6.3 (djgpp v1)
rem  * a very simple make driver
rem  * Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
rem  */

@if "%KB_ECHO%"=="n" echo off

set EXTRA_CFLAGS=

set CC=gcc
set CFLAGS=@b\gcc.opt @b\dos32\dj1.opt %EXTRA_CFLAGS%
set ASFLAGS=-x assembler-with-cpp -Wall
set MYLIB=libkb.a

echo Compiling, please be patient...
%CC% %CFLAGS% -Isrc -c src\*.c
@if errorlevel 1 goto error
if exist %MYLIB% del %MYLIB%
ar rcs %MYLIB% @b\dos32\dj1.rsp
@if errorlevel 1 goto error

set CFLAGS=%CFLAGS% -Iexamples
%CC% -s %CFLAGS% examples\kbtst.c %MYLIB% -o kbtst.out
@if errorlevel 1 goto error
coff2exe kbtst.out
@if errorlevel 1 goto error

echo Done.
goto end
:error
echo error!
:end
@call b\unset.bat
