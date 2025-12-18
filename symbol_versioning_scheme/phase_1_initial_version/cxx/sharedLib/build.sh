g++ -Wall -g -O0 -fPIC -c simple.cpp
g++ -shared simple.o -Wl,--version-script,simpleVersionScript -o libsimple.so

