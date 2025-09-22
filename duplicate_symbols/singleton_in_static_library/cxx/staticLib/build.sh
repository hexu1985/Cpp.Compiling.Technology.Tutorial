# for 64-bit OS must also pass -mcmodel=large compiler flag
g++ -fPIC -Wall -g -O0 -c singleton.cpp
ar -rcs libsingleton.a singleton.o
