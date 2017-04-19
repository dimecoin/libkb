rem /* DOS 16 bit - Borland C 3.1
rem  * a very simple make driver
rem  * Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
rem  */

@if "%KB_ECHO%"=="n" echo off

set CC=bcc -ml
set CFLAGS=-Iinclude -h- -d -O -w
set MYLIB=kb.lib

echo Compiling, please be patient...
%CC% %CFLAGS% -Isrc -c src\*.c
@if errorlevel 1 goto error
if exist %MYLIB% del %MYLIB%
tlib %MYLIB% @b\dos16\bc31.rsp
@if errorlevel 1 goto error

set CFLAGS=%CFLAGS% -Iexamples
%CC% %CFLAGS% examples\kbtst.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% examples\keycodes.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% examples\simple.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% -Isrc examples\tube.c %MYLIB%
@if errorlevel 1 goto error

echo Done.
goto end
:error
echo error!
:end
@call b\unset.bat
