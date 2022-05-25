#!/bin/bash

gcc -o ./chess_bin.o ./src/main.c

if command ; then
    ./chess_bin.o
else 
    echo "Build failed"
fi