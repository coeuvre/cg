@echo off

cd /D %~dp0

set base=%~dp0
set base=%base:~0,-1%

set cc=cl
set cflags=/Od /Oi /fp:fast /Zi /MTd /nologo /W4 -I%base%\include\cg -I%base%\src
set libs=user32.lib gdi32.lib
set ldflags=/Fecg /link %libs%

if not exist %base%\build mkdir build
pushd %base%\build

%cc% %cflags% %base%\src\platform\windows\entry.c %ldflags%

popd