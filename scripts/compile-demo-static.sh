./compile-static-shared.sh
gcc ../demo/demo.c -L ../bin/static -l cglib -lm -o../bin/demo-static -g
../bin/demo-static