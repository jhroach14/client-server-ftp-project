CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=gnu++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

compile: myftp.out

myftp.out: myftp.cpp Socket.o
	$(CC) $(CFLAGS) -o myftp.cpp

Socket.o: Socket.cpp Socket.h
	$(CC) $(CFLAGS) Socket.cpp

run: 
	./myftp.out

clean:
	rm *.o
	rm *.out