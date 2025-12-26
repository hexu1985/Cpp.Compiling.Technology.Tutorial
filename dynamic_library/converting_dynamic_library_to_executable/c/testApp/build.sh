g++ -Wall -O2 -I../sharedLib/exports/ -c src/main.c -o src/main.o
g++  ./src/main.o -lpthread -lm -ldl -L../deploy -lexecutablesharedlib -Wl,-Bdynamic -Wl,-R../deploy -o demoApp

