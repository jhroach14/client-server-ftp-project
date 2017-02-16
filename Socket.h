//
// Created by User on 2/16/2017.
//

#ifndef SERVER_CLIENT_SOCKET_H
#define SERVER_CLIENT_SOCKET_H

#include "lib.h"

#endif //SERVER_CLIENT_SOCKET_H

using namespace std;

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