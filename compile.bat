@echo off
::if nescessary, add -lraymath and -lrlgl, or another flags
::change main.exe to an your preference name.exe
gcc main.c -o main.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
echo file compiled
