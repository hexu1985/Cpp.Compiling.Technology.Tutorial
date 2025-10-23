CC = gcc
CFLAGS = -Wall -g3 -Wall -Wextra

OBJECTS = static_data.c
TARGET = static_data

all: $(TARGET)
	@echo "TARGET = $(TARGET)" 

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

.PHONY:
clean:
	$(RM) $(TARGET) a.out core *.o
	@echo "clean OK!"

