@echo off
rem All Re-Compilation...

call d.bat
call c.bat
if errorlevel 1 goto stop
call e.bat
:stop
