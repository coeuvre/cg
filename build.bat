@echo off

cd /D %~dp0

set base=%~dp0
set base=%base:~0,-1%

set cc=cl
set cflags=/Od /Oi /fp:fast /Zi /MTd /nologo /W4 -I%base%\include\cg -I%base%\src
set ldflags=/INCREMENTAL:NO /OPT:REF

if not exist %base%\build mkdir build
pushd %base%\build

%cc% %cflags% %base%\src\cg.c /LD /Fecg /link %ldflags% /EXPORT:cg_loaded /EXPORT:cg_update

%cc% %cflags% %base%\src\platform\windows\entry.c /Fecg /link user32.lib gdi32.lib %ldflags%

popd