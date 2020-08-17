  
CC = gcc
CFLAGS = -g -O3 -lm -Wall -Wextra -Werror -std=c99

.PHONY: default_target all clean

default_target: Greedy
all: default_target

OBJECTS_GREEDY = $(patsubst %.c, compilados/.obj/%.o, $(wildcard *.c))
HEADERS_GREEDY = $(wildcard *.h)

compilados/.obj/%.o: %.c $(HEADERS_GREEDY)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: Greedy $(OBJECTS_GREEDY)

Greedy: compilados compilados/.obj $(OBJECTS_GREEDY)
	$(CC) $(OBJECTS_GREEDY) $(CFLAGS) -o compilados/$@

compilados:
	mkdir -p $@

compilados/.obj:
	mkdir -p $@

clean:
	-rm -rf compilados
