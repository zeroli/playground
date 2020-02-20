g++ -Wall -g -O0 -fPIC -I. -c shlib.cpp
g++ -shared shlib.o -L. -lsingleton \
    -Wl,--version-script=versionScript \
    -Wl,-soname,libfirst.so.1 -o libfirst.so.1.0.0
ldconfig -n .
ln -sf libfirst.so.1 libfirst.so

