PROJECT = test
SOURCES = hash.c
INCLUDES = hash.h
CFLAGS =

debug: CFLAGS += -g -O0

all debug: $(PROJECT)

$(PROJECT): $(PROJECT).c $(SOURCES) $(INCLUDES)
	gcc $(PROJECT).c $(SOURCES) -o $(PROJECT) $(CFLAGS)

clean:
	rm -f $(PROJECT)
