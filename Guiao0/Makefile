CC = gcc
CFLAGS = -Wall -O2 -Wextra -g


programa: person
	$(CC) $(CFLAGS) main.c -o programa person.o

person:
	$(CC) $(CFLAGS) -c person.c

clean:
	rm programa person.o

