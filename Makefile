PROJECT = test
SOURCES = hash.c
INCLUDES = hash.h
CFLAGS = -Wall
CC = gcc

debug: CFLAGS += -g -O0

all debug: $(PROJECT)

$(PROJECT): $(PROJECT).c $(SOURCES) $(INCLUDES)
	$(CC) $(PROJECT).c $(SOURCES) -o $(PROJECT) $(CFLAGS)

clean:
	rm -f $(PROJECT)
