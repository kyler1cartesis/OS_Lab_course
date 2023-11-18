CC=gcc
CFLAGS=-Wall -Wno-unused-result -O2 -I.

objects = process_memory parallel psum

all: $(objects)

process_memory: process_memory.c
	$(CC) -o process process_memory.c $(CFLAGS)

parallel: utils_obj find_min_max_obj utils.h find_min_max.h
	$(CC) -o parallel utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

psum : utils.h utils_obj sum_lib sum_obj
	$(CC) sum.o utils.o -Lbin -l_sumfunc -o psum -pthread $(CFLAGS)

zombie:
	$(CC) zombie.c -o zombie $(CFLAGS)

sum_lib:
	mkdir bin -p
	$(CC) -fPIC -o bin/sumfunc.o -c sumfunc.c -pthread $(CFLAGS)
	ar rcs bin/lib_sumfunc.a bin/sumfunc.o

sum_obj: 
	$(CC) -o sum.o -c parallel_sum.c -pthread $(CFLAGS)

utils_obj: utils.h utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max_obj: utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

clean:
	rm process find_min_max_obj utils_obj sum_obj psum parallel zombie
	rm bin -r
