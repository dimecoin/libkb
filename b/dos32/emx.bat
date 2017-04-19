rem /* DOS 32 bit - gcc 2.7.2.1 (emx 0.9c)
rem  * a very simple make driver
rem  * Copyright (C) 1996, 1997, 1998 Markus F.X.J. Oberhumer
rem  */

@if "%KB_ECHO%"=="n" echo off

@rem workaround a problem with the RSX extender when running under Win95
set SAVE_LFN=%LFN%
set LFN=n

set EXTRA_CFLAGS=
REM set EXTRA_CFLAGS=-fbounds-checking

set CC=gcc
set CFLAGS=@b\gcc.opt @b\dos32\emx.opt %EXTRA_CFLAGS%
set MYLIB=kb.a

echo Compiling, please be patient...
%CC% %CFLAGS% -c src\*.c
@if errorlevel 1 goto error
if exist %MYLIB% del %MYLIB%
ar rcs %MYLIB% @b\dos32\emx.rsp
@if errorlevel 1 goto error

%CC% -s %CFLAGS% examples\kbtst.c %MYLIB% -o kbtst.exe -lvideo
@if errorlevel 1 goto error
emxbind -aq kbtst.exe -acim
@if errorlevel 1 goto error

echo Done.
goto end
:error
echo error!
:end
set LFN=%SAVE_LFN%
set SAVE_LFN=
@call b\unset.bat
