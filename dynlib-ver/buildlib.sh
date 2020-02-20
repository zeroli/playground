gcc -Wall -g -O0 -fPIC -c simple.c
gcc -shared -Wl,-soname=libsimple.so.1 -Wl,--version-script=versionScript simple.o -o libsimple.so.1.0.0
ldconfig -n .
ln -sf libsimple.so.1 libsimple.so
echo 'building done libsimple.so'
