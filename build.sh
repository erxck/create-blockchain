!/bin/hs

set -xe

GCC=g++
CFLAGS="-Wall -Wextra"

$GCC $CFLAGS -o main main.cpp