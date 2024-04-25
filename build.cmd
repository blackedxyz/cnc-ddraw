@echo off
REM
REM patch environment config
REM
set PATH=C:\w64devkit\bin
make clean
make
REM make DEBUG=1
pause
