CC = g++
DEBUG = -g
CFLAGS = -Wall -std=gnu++11 $(DEBUG) -l./lib.h
LFLAGS = -Wall $(DEBUG)
LIBS = Socket.h lib.h

compile: myftp.out myFtpServer.out

myftp.out: myftp.cpp myftp.h lib.h
	$(CC) $(LIBS) $(CLAGS) myftp.cpp 

myFtpServer.out: myFtpServer.cpp myFtpServer.cpp lib.h
	$(CC) $(CFLAGS) $(LIBS) myFtpServer myFtpServer.o 

run: 
	./myftp.out

clean:
	rm *.o