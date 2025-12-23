gcc -g -O0 -c -I../sharedLib2.0 main.c
gcc main.o -Wl,-L../sharedLib2.0 -lsimple \
           -Wl,-R../sharedLib2.0 -o ver2PeerApp 
