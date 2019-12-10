#!/bin/sh
#compile all C files of the source folder into the bin folder
for file in ../src/*.c
do
	gcc -o -std=c99 "../bin/$(basename "$file" .c)" "$file"  
  done