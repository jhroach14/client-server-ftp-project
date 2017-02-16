#ifndef SERVER_CLIENT_MYFTPSERVER_H
#define SERVER_CLIENT_MYFTPSERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <stdbool.h>
#include <cstdio>
#include <signal.h>

#endif //SERVER_CLIENT_MYFTPSERVER_H

using namespace std;

void fatal_error(string output);
void error(string output);

struct Socket{
	int socketFd;
	int clientFd;
	unsigned int portNum;
	char buffer[256];
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	socklen_t clientLength;


	Socket(unsigned int portNum);
	void bindAndListen();
	void acceptConnection();
	string getInput();
	void toClient(string message);
	void shutDown();

};