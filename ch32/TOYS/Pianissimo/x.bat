@echo off
rem Rebuild and write...

call c.bat
if errorlevel 1 goto stop
call e.bat
:stop
