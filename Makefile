CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lncurses

timeshit: timeshit.c timeshit.h
	$(CC) $(CFLAGS) timeshit.c $(LDLIBS) -o timeshit