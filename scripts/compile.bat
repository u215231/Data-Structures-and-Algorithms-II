echo off
cd ..
md build_windows 2>nul
cd build_windows
nmake all
cd ..\scripts