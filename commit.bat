set path=%path%;L:\programmas\git\bin\
@echo off
set /p commitmsg=bericht?
git commit -a -m "%commitmsg%"
pause