# Makefile for Fruit Catcher Game

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm

SRC = main.c
HEADERS = menu.h Draw.h color.h text_art.h

fruit_catcher: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBS)

.PHONY: clean

clean:
	rm -f fruit_catcher
