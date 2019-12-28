CC=gcc
CFLAGS=-g3

all: test_avlTree

test: all
	valgrind -q --leak-check=yes ./test_avlTree

test_avlTree: test_avlTree.o avlTree.o
	$(CC) $(CFLAGS) -o $@ $^

test_avlTree.o avlTree.o: avlTree.h

clean:
	$(RM) test_avlTree *.o
