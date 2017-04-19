rem /* DOS 16 bit - Microsoft C 7.0
rem  * a very simple make driver
rem  * Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
rem  */

@if "%KB_ECHO%"=="n" echo off

set CC=cl -nologo -f- -AL
set CFLAGS=-Iinclude -O -G2 -W3
set MYLIB=kb.lib

echo Compiling, please be patient...
%CC% %CFLAGS% -c src\*.c
@if errorlevel 1 goto error
if exist %MYLIB% del %MYLIB%
lib /nologo %MYLIB% @b\dos16\mc70.rsp,nul
@if errorlevel 1 goto error

%CC% %CFLAGS% examples\kbtst.c %MYLIB% graphics.lib
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
