#!/bin/bash

mkdir -p outlibs
cd libs
    for lib in $(find *.c); do
        gcc -c $lib -o ../outlibs/$lib.o
    done
cd ..