CC = gcc
CFLAGS = -g -Wall
objects = main.o location.o parsexec.o

default: all


all: $(objects)
	$(CC) $^ -o prog

$(objects): %.o: %.c
	$(CC) -c $^ -o $@

clean: 
	rm -f *.c *.o all