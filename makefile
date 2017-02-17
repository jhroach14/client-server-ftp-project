CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=gnu++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

compile: myftp.out myFtpServer.out

myftp.out: myftp.cpp Socket.h
	$(CC) $(CFLAGS) myftp.cpp 

myFtpServer.out: myFtpServer.cpp myFtpServer.h Socket.h
	$(CC) $(CFLAGS) myFtpServer.cpp 

run: 
	./myftp.out

clean:
	rm *.o