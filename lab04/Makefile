# Setup a variable to reference the desired compiler
CC = gcc
SRC = src
BIN = bin

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

$(BIN)/warmup: $(SRC)/warmup.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $(BIN)/warmup


test:
	$(BIN)/warmup
	$(BIN)/activity

clean:
	rm -f *.o *.d a.out $(BIN)/*
