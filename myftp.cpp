#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Socket.h"

int main(int argc, char* argv[]){
	int sockfd, portNum;
	ssize_t len;
	FILE* toSend, toReceive;

	if(argc < 3){
		printf("Usage %s hostname port\n", argv[0]);
	}

	Socket * mySocket = new Socket(80);
	mySocket->connectToServer(argv[1], atoi(argv[2]));
	string input;

	while(true){
		cout << "myftp>";
		cin >> input;
		if(input.compareTo("quit") == 0){
			mySocket->close;
			exit(0);
		}
		else if(input.substr(0,3).compareTo("get") == 0){
			mySocket->sendOutputToServer(input);
			recv(mySocket, mySocket->buffer, 256, 0);
			int index = input.find(" ");
			string fileName = input.substr(index);
			int fileSize = atoi(mySocket->buffer);
			toReceive = fopen(fileName, "w");
			int remainSize = fileSize;
			while((len = recv(mySocket, mySocket->buffer, 256, 0) > 0 && remainSize > 0){
				fwrite(mySocket->buffer, sizeof(char), len, toReceive);
				remainSize -= len;
			}
			fclose(toReceive);

		}
		else if(input.substr(0,3).compareTo("put") == 0){

		}
		mySocket->sendOutputToServer(input);


	}
}
