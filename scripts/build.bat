echo off
cd ..
md build_windows 2>nul
cd build_windows
cmake -G "NMake Makefiles" ..
cd ..\scripts