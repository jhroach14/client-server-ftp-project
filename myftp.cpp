#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Socket.h"
//#include "Socket.cpp"

int main(int argc, char* argv[]){
	ssize_t len;
	FILE* sendFile;
	FILE* receiveFile;

	if(argc < 3){
		printf("Usage %s hostname port\n", argv[0]);
	}

	Socket * mySocket = new Socket((unsigned int)80);
	mySocket->connectToServer(argv[0], atoi(argv[1]));
	string input;

	while(true){
		cout << "myftp>";
		cin >> input;
		if(input.compare("quit") == 0){
				mySocket->shutDown();
				exit(0);
		}
		size_t found = input.find(" ");
		if(found != string::npos){
			char* inputArr = new char[input.length() + 1];
			string firstWord(strtok(inputArr, " "));
			if(firstWord.compare("get") == 0){
				int index = input.find(" ");
				string fileName = input.substr(index);
				receiveFile = fopen(fileName.c_str(), "w");
				while((len = recv(mySocket->mySocketFd, mySocket->buffer, 256, 0) > 0)){
					fwrite(mySocket->buffer, sizeof(char), len, receiveFile);
				}
				fclose(receiveFile);

			}
			else if(firstWord.compare("put") == 0){
				int index = input.find(" ");
				string fileName = input.substr(index);
				//Set to r so it reads, if opened with w it destroys the data
				sendFile = fopen(fileName.c_str(), "r");
				fseek(sendFile, 0, SEEK_END);
				int size = ftell(sendFile);
				rewind(sendFile);
				char* sendBuffer[size];
				fwrite(sendBuffer, sizeof(char), size, sendFile);
				while(1){
					int bytes_read = read(sendFile, sendBuffer, sizeof(sendBuffer));
					if(bytes_read == 0)break;
					void *p = sendBuffer;
					while(bytes_read > 0){
						int bytes_written = write(mySocket->mySocketFd, p, bytes_read);
						bytes_read -= bytes_written;
						p += bytes_written;
					}
				}

			}
		}
		else{
			mySocket->sendOutputToServer(input);
		}
		


	}
}
