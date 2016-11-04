@echo off

if "%1" == "clean" goto :clean

if exist %~dp0build goto build

mkdir build
pushd %~dp0build
cmake -G "Visual Studio 14 Win64" ..
popd

:build
cmake --build build
goto :eof

:clean
if exist %~dp0build rmdir %~dp0build /s/q
goto :eof

