g++ -Wall -g -O0 -I. -c main.cpp
g++ main.o -L. -lsingleton \
    -L. -lfirst \
    -L. -lsecond \
    -Wl,-R. \
    -o clientApp
