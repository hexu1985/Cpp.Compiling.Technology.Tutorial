g++ -g -O0 -c -I../sharedLib main.cpp
g++ main.o -Wl,-L../sharedLib -lsimple \
           -Wl,-R../sharedLib -o newerApp
