CC = gcc
TARGET = trackray
SRCS = trackray.c

RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS = $(shell pkg-config --libs raylib)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(RAYLIB_CFLAGS) $(RAYLIB_LIBS)

.PHONY: clean
clean:
	rm -f $(TARGET)
