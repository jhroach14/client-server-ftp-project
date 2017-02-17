CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=gnu++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

compile: myftp.out

myftp.out: myftp.cpp Socket.h
	$(CC) $(CFLAGS) myftp.cpp -o myftp.out

run: 
	./myftp.out

clean:
	rm *.out