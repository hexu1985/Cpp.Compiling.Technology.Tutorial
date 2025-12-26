g++ -Wall -O0 -fPIC -I./exports/ -c src/executableSharedLib.c -o src/executableSharedLib.o
g++ -shared -Wl,-e,main ./src/executableSharedLib.o -lpthread -lm -ldl -o libexecutablesharedlib.so
mkdir -p ../deploy
cp libexecutablesharedlib.so ../deploy

