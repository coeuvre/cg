@echo off

cd /D %~dp0

set base=%~dp0
set base=%base:~0,-1%

set cc=cl
set cflags=/Od /Oi /fp:fast /Zi /MTd /nologo /W4 -I%base%\include -I%base%\src
set ldflags=/INCREMENTAL:NO /OPT:REF

if not exist %base%\build mkdir build
pushd %base%\build

del *.pdb > NUL 2> NUL

%cc% %cflags% %base%\src\cg.c /Fmcg.map /LD /Fecg /link %ldflags% /PDB:cg_%random%.pdb /EXPORT:cg_loaded /EXPORT:cg_update

%cc% %cflags% %base%\src\platform\windows\entry.c /Fecg /link user32.lib gdi32.lib opengl32.lib %ldflags%

popd