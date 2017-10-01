@echo off

set FLAGS=-Wall -w -g -ggdb -std=c++11 -m32
set LINKER=-static-libstdc++ -static-libgcc -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf 

set INCLUDE=-I"C:/MinGW/SDL2-2.0.5/i686-w64-mingw32/include"
set LIB=-L"C:/MinGW/SDL2-2.0.5/i686-w64-mingw32/lib"

set OBJ="obj/Debug/main.o"
set CPP="C:/Users/gorta/OneDrive/Dokumenty/Emilcia/main.cpp"
set EXE="bin/Debug/em.exe"


mingw32-g++.exe %FLAGS% %INCLUDE% -c %CPP% -o %OBJ% 2> compile_out.log || goto error_compile
mingw32-g++.exe %FLAGS% %LIB% -o %EXE% %OBJ% %LINKER% 2> linker_out.log || goto error_linker

del /q compile_out.log linker_out.log 2>&1 > nul

C:\Users\gorta\OneDrive\Dokumenty\Emilcia\bin\debug\em.exe

exit
:error_compile
type compile_out.log
pause>nul
exit

:error_linker
type linker_out.log
pause>nul