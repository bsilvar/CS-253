# Setup a variable to reference the desired compiler
CC = gcc
SRC = src
BIN = bin
ETC = etc

# Setup a variable to hold desired compiler flags
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=gnu99 -g

# Declaring the build, test and clean rules as phony means that no artifact
#   is created by these rules with a cooresponding name.  Therefore, the
#   rule should run when executed.
.PHONY: build test clean

# The build rule depends upon the myprog artifact existing.  If it does not, make
#   will look for a rule to create it.
build: $(BIN)/mycat $(BIN)/mygrep $(BIN)/mysort $(BIN)/mywc


$(BIN)/mycat: $(SRC)/mycat.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

memtest-mycat: $(BIN)/mycat
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes $(BIN)/mycat -f /usr/share/dict/american-english > /dev/null

$(BIN)/mygrep: $(SRC)/mygrep.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

memtest-mygrep: $(BIN)/mygrep
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes $(BIN)/mygrep -f /usr/share/dict/american-english -s tree > /dev/null

$(BIN)/mysort: $(SRC)/mysort.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

memtest-mysort: $(BIN)/mysort
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes $(BIN)/mysort -f /usr/share/dict/american-english -r > /dev/null

$(BIN)/mywc: $(SRC)/mywc.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ 

memtest-mywc: $(BIN)/mywc
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes $(BIN)/mywc -f /usr/share/dict/american-english > /dev/null


clean:
	rm -f *.o *.d a.out $(BIN)/*
