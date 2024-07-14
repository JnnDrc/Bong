#!/bin/bash

# Shell script to compile a C program on Linux
# Checks for raylib installation and installs it if not found

echo "Checking for raylib installation..."

# Check if raylib library is installed
if ! pkg-config --exists raylib; then
    echo "raylib not found. Installing..."

    # Check the distribution type to determine package manager
    if [ -f /etc/os-release ]; then
        source /etc/os-release
        if [ "$ID" = "debian" ] || [ "$ID" = "ubuntu" ]; then
            sudo apt-get update
            sudo apt-get install -y raylib-dev
        elif [ "$ID" = "fedora" ]; then
            sudo dnf install -y raylib-devel
        elif [ "$ID" = "arch" ] || [ "$ID" = "manjaro" ]; then
            sudo pacman -Syu --noconfirm raylib
        else
            echo "Unsupported distribution. Please install raylib manually."
            exit 1
        fi
    else
        echo "Unknown distribution. Please install raylib manually."
        exit 1
    fi
fi

# Compilation command
echo "Compiling the program..."

gcc main.c -o main -lraylib

# Check compilation result
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable: ./main"
else
    echo "Compilation failed."
fi


