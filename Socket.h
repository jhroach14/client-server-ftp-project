//
// Created by User on 2/16/2017.
//

#ifndef SERVER_CLIENT_SOCKET_H
#define SERVER_CLIENT_SOCKET_H

#include "lib.h"

#endif //SERVER_CLIENT_SOCKET_H

using namespace std;

struct Socket{
	int mySocketFd;
	int newSocketFd;
	unsigned int portNum;
	char buffer[256];
	struct sockaddr_in myAddress;
	struct sockaddr_in peerAddress;
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