@echo off
echo Cleaning old files...

del *.sln >nul 2>&1
rmdir /s /q bin >nul 2>&1
rmdir /s /q bin-int >nul 2>&1

echo Generating Visual Studio 2022 project...
call .\tools\premake\premake5.exe vs2022

echo Done!
pause