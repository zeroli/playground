gcc -Wall -g -O0 -I. -c main.c
gcc main.o -L. -lstaticlib -lshlib -Wl,-R. -o clientApp
