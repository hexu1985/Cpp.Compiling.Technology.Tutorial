rm -rf *.o

g++ -Wall -g -O0 -c main.cpp
g++ main.o -o clientAppC++

g++ -Wall -g -O0 -c main2.cpp
g++ main2.o -o clientAppC++2
