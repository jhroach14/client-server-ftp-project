//
// Created by User on 2/16/2017.
//

#ifndef SOCKET_H
#define SOCKET_H

#include "lib.h"

 //SERVER_CLIENT_SOCKET_H

using namespace std;

struct Socket{
	int mySocketFd;
	int newSocketFd;
	unsigned int portNum;
	char buffer[256];
	sockaddr_in myAddress;
	sockaddr_in peerAddress;
	socklen_t socketLength;
	struct hostent *server;


	Socket(unsigned int portNum);
	void bindAndListen();
	void acceptConnectionFromClient();
	string getInputFromClient();
	void sendOutputToClient(string message);
	string getInputFromServer();
	void sendOutputToServer(string message);
	void connectToServer(string domainName, int port);
	void shutDown();

};

#endif