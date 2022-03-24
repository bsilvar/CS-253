# Setup a variable to reference the desired compiler
CC = gcc
SRC = src
INC = include
BIN = bin

# Setup a variable to hold desired compiler flags
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=gnu99 -g

# Declaring the build, test and clean rules as phony means that no artifact
#   is created by these rules with a cooresponding name.  Therefore, the
#   rule should run when executed.
.PHONY: build test clean

# The build rule depends upon the myls artifact existing.  If it does not, make
#   will look for a rule to create it.
build: $(BIN)/myls


$(BIN)/myls: $(SRC)/activity.c #$(SRC)/warmup.c  
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

memtest: $(BIN)/myls
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes $(BIN)/myls  -d /home/student -s -h

clean:
	rm -f *.o *.d a.out myls mytests main
