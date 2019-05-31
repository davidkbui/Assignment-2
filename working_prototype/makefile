CC = gcc
CFLAGS = -Wall -ansi -lm



test.out : main.o encryption.o interface.o
	$(CC) $(CFLAGS) -o test.out main.o encryption.o interface.o

encryption.o: encryption.c encryption.h
	$(CC) $(CFLAGS) -c -o encryption.o encryption.c

interface.o: interface.c interface.h
	$(CC) $(CFLAGS) -c -o interface.o interface.c



clean:
	rm test.out main.o encryption.o interface.o
