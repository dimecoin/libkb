rem /* DOS 32 bit - Watcom C 10.5
rem  * a very simple make driver
rem  * Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
rem  */

@if "%KB_ECHO%"=="n" echo off
REM set WCGMEMORY=4096
REM set WCGMEMORY=?

set _CC=wcl386 -zq -mf -5r -bt#dos
set CFLAGS=-Iinclude -wx -oneatx
set MYLIB=kb.lib

echo Compiling, please be patient...
set CC=%_CC%
REM set CC=%CC% -cc++
%CC% %CFLAGS% -zc -c src\*.c
@if errorlevel 1 goto error
if exist %MYLIB% del %MYLIB%
wlib -q -b -n -t %MYLIB% @b\dos32\wc105.rsp
@if errorlevel 1 goto error

set CC=%_CC% -zc -l#dos4g
%CC% %CFLAGS% examples\kbtst.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% examples\keycodes.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% examples\sigalrm.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% examples\simple.c %MYLIB%
@if errorlevel 1 goto error
%CC% %CFLAGS% -Isrc examples\tube.c %MYLIB%
@if errorlevel 1 goto error
@goto done

%CC% %CFLAGS% -Isrc -DUSE_SEAL examples\tube.c %MYLIB% audio.lib
@if errorlevel 1 goto error
@goto done

:done
echo Done.
goto end
:error
echo error!
:end
@call b\unset.bat
