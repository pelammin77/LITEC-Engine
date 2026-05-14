@echo off
echo Cleaning generated Makefile files...

if exist Makefile (
    del Makefile
    echo Deleted Makefile
)

if exist *.make (
    del *.make
    echo Deleted *.make files
)

echo Makefile cleanup completed.
pause