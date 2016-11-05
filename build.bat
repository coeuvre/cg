@echo off

if not exist %~dp0build goto generate

:Debug
cmake %~dp0build
cmake --build %~dp0build --config Debug
goto :eof

:generate
mkdir build
pushd %~dp0build
cmake -G "Visual Studio 14 Win64" ..
popd
goto :Debug
