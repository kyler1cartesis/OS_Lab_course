CC=gcc
CFLAGS=-Wall -Wno-unused-result -O2

objects = fact deadlock mutex_with mutex_not

all: $(objects)

mutex_with: mutex.c
	$(CC) -o mutex_with mutex.c -D MUTEX -pthread $(CFLAGS)

mutex_not: mutex.c
	$(CC) -o mutex_not mutex.c -pthread $(CFLAGS)

fact : utils.h utils.o fact.c
	$(CC) -o fact utils.o fact.c -pthread $(CFLAGS)

deadlock: deadlock.c
	$(CC) -o deadlock deadlock.c -pthread $(CFALGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

clean :
	rm utils.o all