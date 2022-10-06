cd build
@echo off
set /p curname=name: 
set /p cursession=session: 
@echo on
api-test.exe --name %curname% --session %cursession%
cd ../