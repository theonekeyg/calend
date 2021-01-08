CC = gcc
CFLAGS = -g -Wall
SRCS := $(shell find src/ -type f -iname \*.c -printf "%f\n")
OBJ = $(addprefix obj/, $(SRCS:.c=.o))
BIN = calend

VPATH = src/

all: $(BIN)

-include obj/*.d

obj/%.o: %.c
	@mkdir -p obj
	$(CC) -c -o $@ $< -MMD $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
