# Setup a variable to reference the desired compiler
CC = gcc
SRC = src
BIN = bin
OBJ = obj

# Setup a variable to hold desired compiler flags
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g

# Declaring the build, test and clean rules as phony means that no artifact
#   is created by these rules with a cooresponding name.  Therefore, the
#   rule should run when executed.
.PHONY: build test clean

build: $(BIN)/activity $(BIN)/warmup

$(BIN)/activity: $(SRC)/activity.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $(BIN)/activity

$(BIN)/activity-v2:
	mkdir -p $(OBJ)
	gcc -E $(SRC)/activity.c -o $(OBJ)/activity.i
	gcc -S $(OBJ)/activity.i -o $(OBJ)/activity.s
	as $(OBJ)/activity.s -o $(OBJ)/activity.o
	ld /usr/lib64/crti.o /usr/lib64/crtn.o /usr/lib64/crt1.o /usr/lib64/libc.so  obj/activity.o  -o $(BIN)/activity-v2

$(BIN)/warmup: $(SRC)/warmup.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $(BIN)/warmup


test:
	$(BIN)/warmup
	$(BIN)/activity

clean:
	rm -f *.o *.d a.out $(BIN)/* $(OBJ)/*
