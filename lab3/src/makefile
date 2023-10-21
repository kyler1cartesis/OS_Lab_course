CC=gcc
CFLAGS=-Wall -O2 -I.
objects = exec_seq min_max_seq min_max_par

all: $(objects)

min_max_seq : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o min_max_seq find_min_max.o utils.o sequential_min_max.c $(CFLAGS)

min_max_par : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o min_max_par utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

exec_seq: utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o exec_seq utils.o find_min_max.o exec_seq.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

clean :
	rm utils.o find_min_max.o min_max_seq min_max_par
