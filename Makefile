CC = gcc
CFLAGS = -W -Wall
TARGET = app
OBJECTS = main.o class.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(TARGET)