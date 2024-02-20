#!/usr/bin/bash

FILE_NAME=$1
echo Compiling $FILE_NAME...

g++ -Wall -std=c++17 $FILE_NAME -o prog
