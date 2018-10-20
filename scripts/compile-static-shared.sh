#!/bin/sh

#static compilation
gcc -c       ../src/cglib.c    -o ../bin/static/cglib.o
gcc -c       ../src/color.c    -o ../bin/static/color.o
gcc -c       ../src/doughnut.c -o ../bin/static/doughnut.o
gcc -c       ../src/pie.c -o ../bin/static/pie.o
gcc -c       ../src/graph.c    -o ../bin/static/graph.o
gcc -c       ../src/hbar.c     -o ../bin/static/hbar.o
gcc -c       ../src/vbar.c     -o ../bin/static/vbar.o

ar rcs ../bin/static/libcglib.a \
../bin/static/cglib.o \
../bin/static/color.o \
../bin/static/doughnut.o \
../bin/static/graph.o \
../bin/static/hbar.o \
../bin/static/vbar.o \
../bin/static/pie.o \

#shared compilation
gcc -c -fPIC ../src/cglib.c    -o ../bin/shared/cglib.o
gcc -c -fPIC ../src/color.c    -o ../bin/shared/color.o
gcc -c -fPIC ../src/doughnut.c -o ../bin/shared/doughnut.o
gcc -c -fPIC ../src/graph.c    -o ../bin/shared/graph.o
gcc -c -fPIC ../src/hbar.c     -o ../bin/shared/hbar.o
gcc -c -fPIC ../src/vbar.c     -o ../bin/shared/vbar.o
gcc -c -fPIC ../src/pie.c      -o ../bin/shared/pie.o

gcc -shared \
../bin/shared/cglib.o \
../bin/shared/color.o \
../bin/shared/doughnut.o \
../bin/shared/graph.o \
../bin/shared/hbar.o \
../bin/shared/vbar.o \
../bin/shared/pie.o \
-o ../bin/shared/libcglib.so