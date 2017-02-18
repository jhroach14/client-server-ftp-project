#include "lib.h"
#include "myftp.h"

int main(int argc, char* argv[]){
	ssize_t len;
	FILE* sendFile;
	FILE* receiveFile;

	if(argc < 2){
		printf("Usage %s hostname port\n", argv[0]);
	}

	//Creates socket
	Socket * mySocket = new Socket((unsigned int)argv[2]);
	string input;

	//"Shell" loop
	while(true){
		//Connect to server
		mySocket->bindAndListen();
		cout << "SOCKET BOUND";
		mySocket->connectToServer(argv[0], atoi(argv[1]));
		cout << "SOCKET CONNECTED TO SERVER";
		//Get user input
		cout << "myftp>";
		cin >> input;
		if(input.compare("quit") == 0){
				mySocket->shutDown();
				exit(0);
		}
		mySocket->sendOutputToServer(input);
		size_t found = input.find(" ");
		if(found != string::npos){
			char* inputArr = new char[input.length() + 1];
			string firstWord(strtok(inputArr, " "));
			
			//Getting a file from remote host
			if(firstWord.compare("get") == 0){
				int index = input.find(" ");
				string fileName = input.substr(index);
				receiveFile = fopen(fileName.c_str(), "w");
				while((len = recv(mySocket->mySocketFd, mySocket->buffer, 256, 0) > 0)){
					fwrite(mySocket->buffer, sizeof(char), len, receiveFile);
				}
				fclose(receiveFile);

			}
			//Sending a file to remote host
			else if(firstWord.compare("put") == 0){
				int index = input.find(" ");
				string fileName = input.substr(index);
				sendFile = fopen(fileName.c_str(), "r");
				fseek(sendFile, 0, SEEK_END);
				long size = ftell(sendFile);
				rewind(sendFile);
				char sendBuffer[size];
				fgets(sendBuffer, size, sendFile);
				int n;
				while((n = fread(sendBuffer, sizeof(char), size, sendFile)) > 0){
					if(send(mySocket->mySocketFd, sendBuffer, n, 0) < 0){
						cout << "Error sending file";
					}
					bzero(sendBuffer, size);
				}
			}
		}
		//Shutdown connection to be repopened on next iteration of loop
		shutdown(mySocket->mySocketFd, 2);
	}
}
