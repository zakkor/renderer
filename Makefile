TARGET = renderer
LIBS = -lglfw -lGL -lGLEW `pkg-config --libs glib-2.0` `pkg-config --libs graphene-1.0` -lgsl -lgslcblas -lm -lSOIL
CC = gcc
CFLAGS = -g -Wall `pkg-config --cflags glib-2.0` `pkg-config --cflags graphene-1.0`

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

build/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o build/$@

clean:
	-rm build/*.o
	-rm build/$(TARGET)

run:
	./build/$(TARGET)
