CC = g++
DEBUG = -g
CFLAGS = -Wall -std=gnu++11 $(DEBUG) 
LFLAGS = -Wall $(DEBUG)

compile: myftp.out myFtpServer.out

myftp.out: myftp.cpp Socket.cpp
	$(CC) $(CLAGS) -o myftp myftp.cpp Socket.cpp lib.cpp

myFtpServer.out: myFtpServer.cpp Socket.cpp
	$(CC) $(CFLAGS) -o myFtpServer myFtpServer.cpp Socket.cpp lib.cpp

run: 
	./myftp.out

clean:
	rm *.o