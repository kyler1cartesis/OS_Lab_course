CC=gcc
CFLAGS=-Wall -Wno-unused-result -O2 -I. # для подключения библиотек
DEFINES = -BUFSIZE
objects = tcp udp

all: $(objects)

tcp:
	$(CC) -o tcpc tcpclient.c -pthread -D gerg=100 $(CFLAGS)
	$(CC) -o tcps tcpserver.c -pthread -D gerg=100 -D serv=10050 $(CFLAGS)

tcps:
	./tcps &

tcpc:
	./tcpc 127.0.0.1 10050

udp:
	$(CC) -o udps udpserver.c -pthread -D gerg=1024 -D serv=20002 $(CFLAGS)
	$(CC) -o udpc udpclient.c -pthread -D gerg=1024 -D serv=20002 $(CFLAGS)

udps:
	./udps &
	
udpc:	
	./udpc 127.0.0.1:20002

clean : clean_tcp clean_udp

clean_tcp:
	fuser -k 10050/tcp

clean_udp:
	fuser -k udps