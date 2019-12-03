#!/bin/sh
#compile all C files of the source folder into the bin folder
for file in ../src/*.c
do
	gcc -o "../bin/$(basename "$file" .c)" "$file"  
  done