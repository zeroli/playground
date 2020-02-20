gcc -g -O0 -c main.c
gcc main.o -Wl,-L. -lsimple -Wl,-R. -o app2 
