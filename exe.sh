#!/bin/bash
gcc -c dmq.c main.c
gcc -o exe main.c dmq.c
./exe
rm exe main.o dmq.o
