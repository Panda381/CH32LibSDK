@echo off
rem Compilation... Compile all projects in all sub-directories

for /D %%d in (*) do call :comp1 %%d
exit /b

rem Sub-batch to compile one project in %1 subdirectory, as %2 device.
:comp1
if not exist %1\c.bat goto stop
cd %1
echo.
echo ======== Compiling %1 ========
call c.bat
cd ..
:stop
