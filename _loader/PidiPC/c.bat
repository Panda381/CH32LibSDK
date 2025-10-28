@echo off
rem Compilation...
call ..\..\_c1.bat
loaderbin\LoaderBin.exe Loader.bin ..\loader_PidiPC.S
