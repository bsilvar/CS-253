# Setup a variable to reference the desired compiler
CC = gcc
BIN = bin
ETC = etc
SRC = src

# Setup a variable to hold desired compiler flags
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=gnu99 -g

# Declaring the build, test and clean rules as phony means that no artifact
#   is created by these rules with a cooresponding name.  Therefore, the
#   rule should run when executed.
.PHONY: build test clean

# The build rule depends upon the myprog artifact existing.  If it does not, make
#   will look for a rule to create it.
build: $(BIN)/warmup $(BIN)/warmuptests $(BIN)/activity $(BIN)/activitytests 

$(BIN)/warmup: $(SRC)/warmup.c $(SRC)/Song.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BIN)/warmuptests: $(SRC)/warmuptests.c $(SRC)/Song.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BIN)/activity: $(SRC)/activity.c $(SRC)/Student.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BIN)/activitytests: $(SRC)/activitytests.c $(SRC)/Student.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

clean:
	rm -f *.o *.d $(BIN)/*
