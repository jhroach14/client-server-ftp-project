#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Socket.h"
//#include "Socket.cpp"

int main(int argc, char* argv[]){
	int sockfd, portNum;
	ssize_t len;
	FILE* sendFile;
	FILE* receiveFile;

	if(argc < 3){
		printf("Usage %s hostname port\n", argv[0]);
	}

	Socket * mySocket = new Socket(80);
	mySocket->connectToServer(argv[1], atoi(argv[2]));
	string input;

	while(true){
		cout << "myftp>";
		cin >> input;
		if(input.compare("quit") == 0){
			mySocket->shutDown();
			exit(0);
		}
		else if(input.substr(0,3).compare("get") == 0){
			mySocket->sendOutputToServer(input);
			int fileSize = recv(mySocket->mySocketFd, mySocket->buffer, 256, 0);
			int index = input.find(" ");
			string fileName = input.substr(index);
			receiveFile = fopen(fileName.c_str(), "w");
			int remainSize = fileSize;
			while((len = recv(mySocket->mySocketFd, mySocket->buffer, 256, 0) > 0 && remainSize > 0)){
				fwrite(mySocket->buffer, sizeof(char), len, receiveFile);
				remainSize -= len;
			}
			fclose(receiveFile);

		}
		else if(input.substr(0,3).compare("put") == 0){

		}
		else{
			mySocket->sendOutputToServer(input);
		}
		


	}
}
