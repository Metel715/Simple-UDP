#IDIR =../include/include.h
CC=gcc
CFLAGS= -I -O2 -Wall -pedantic -ansi
objects = UDP_IPv6_server.o client.o
#LDIR=../lib


vpath %.h ../include/
vpath %.c ../lib/

all: $(objects)
		$(CC) UDP_IPv6_server.o -o UDP_IPv6_server 
		$(CC) client.c -o client
		


.PHONY: clean	

clean:
		rm -rf *.o *.out
