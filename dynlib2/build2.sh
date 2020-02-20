g++ -Wall -g -O0 -fPIC -I. -c shlib2.cpp
g++ -shared shlib2.o -L. -lsingleton \
    -Wl,--version-script=versionScript2 \
    -Wl,-soname,libsecond.so.1 -o libsecond.so.1.0.0
ldconfig -n .
ln -sf libsecond.so.1 libsecond.so

