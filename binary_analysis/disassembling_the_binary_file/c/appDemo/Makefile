CC = gcc
CFLAGS = -g3 -Wall -Wextra -fPIC
LDFLAGS = -Wl,-rpath,'$$ORIGIN' -Wl,--enable-new-dtags

OBJECTS = main.o
TARGET = appDemo

LIB_OBJS = function.o
LIB_NAME = libdemo.so

all: $(TARGET)
	@echo "TARGET = $(TARGET)" 

$(TARGET): $(OBJECTS) $(LIB_NAME)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIB_NAME): $(LIB_OBJS)
	$(CC) -shared -o $@ $^

.PHONY:
clean:
	$(RM) $(TARGET) $(LIB_NAME) a.out core *.o
	@echo "clean OK!"
