echo off
set "TARGET=..\build_windows"
if exist "%TARGET%" (
    rd /s /q "%TARGET%"
)
md "%TARGET%"
