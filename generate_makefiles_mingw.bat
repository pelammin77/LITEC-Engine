@echo off
echo Generating MinGW Makefiles for LITEC Engine...

tools\premake\premake5.exe --file=premake5_mingw.lua gmake2

if %ERRORLEVEL% neq 0 (
    echo Premake failed.
    pause
    exit /b %ERRORLEVEL%
)

echo MinGW Makefiles generated successfully.
pause