CC = gcc
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces -I./include/ -L./include/ -lraylib
WNDFLAGS = -lopengl32 -lgdi32 -lwinmm
LNXFLAGS = -lm -lpthread -ldl -lrt -lX11

.PHONY: windows
windows:
	$(CC) -o bong.exe main.c $(CFLAGS) $(WNDFLAGS) 

.PHONY: linux
linux:
	$(CC) -o bong main.c $(CFLAGS) $(LNXFLAGS) 
	