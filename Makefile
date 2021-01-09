CC = gcc
CFLAGS = -g -Wall
SRCS := $(shell find src/ -type f -iname \*.c -printf "%f\n")
OBJ = $(addprefix obj/, $(SRCS:.c=.o))
BIN = calend
PREFIX ?= /usr/local

VPATH = src/

.PHONY: install clean

all: $(BIN)

install:
	install -D $(BIN) -t $(PREFIX)/bin

-include obj/*.d

obj/%.o: %.c
	@mkdir -p obj
	$(CC) -c -o $@ $< -MMD $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf obj/ $(BIN)
