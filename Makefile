TARGET = prog
LIBS = -Wl,-Bstatic -lglfw3
CC = gcc
CFLAGS = -g -Wall
LIB_DIR = C:\Libraries

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(LIB_DIR)\include -L$(LIB_DIR)\lib -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -I$(LIB_DIR)\include -L$(LIB_DIR)\lib -Wall $(LIBS) -o $@

clean:
	-del *.o
	-del $(TARGET).exe

run:
	$(TARGET).exe
