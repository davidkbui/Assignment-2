CC = gcc
CFLAGS = -Wall -ansi -lm



test.out : main.o admin.o encryption.o interface.o student.o
	$(CC) $(CFLAGS) -o test.out main.o admin.o encryption.o interface.o student.o

admin.o: admin.c admin.h
	$(CC) $(CFLAGS) -c -o admin.o admin.c

encryption.o: encryption.c encryption.h
	$(CC) $(CFLAGS) -c -o encryption.o encryption.c

interface.o: interface.c interface.h student.h
	$(CC) $(CFLAGS) -c -o interface.o interface.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c -o student.o student.c

clean:
	rm test.out admin.o encryption.o interface.o student.o
