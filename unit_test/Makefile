#!/usr/bin/make

CFLAGS=-g -Wall -I..
RANL=ranlib
LDFLAGS=-L..
LDLIBS=-lbig32
EXES=int128test

all:	int128test

int128test:	int128test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
clean:
	rm -f $(EXES)
	rm -f *.o *.epio

