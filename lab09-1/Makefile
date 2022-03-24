# Setup a variable to reference the desired compiler
CC = gcc

# Setup a variable to hold desired compiler flags
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g

# Declaring the build, test and clean rules as phony means that no artifact
#   is created by these rules with a cooresponding name.  Therefore, the
#   rule should run when executed.
.PHONY: build test clean

# The build rule depends upon the myprog artifact existing.  If it does not, make
#   will look for a rule to create it.
build: bin/activity bin/warmup 

bin/warmup: src/warmup.c src/ContactNode.c 
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@ 

bin/activity: src/activity.c src/PlaylistNode.c
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@ 

test:
	./bin/activity

clean:
	rm -f *.o *.d a.out myprog mytests main
