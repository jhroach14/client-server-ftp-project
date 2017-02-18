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
	Socket * mySocket = new Socket((unsigned int)9000);
	string input;

	//"Shell" loop
	while(true){
		//Connect to server
		mySocket->bindAndListen();
		mySocket->connectToServer(argv[1], argv[2]);
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
				sendFile = fopen(fileName.c_str(), "w");
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
		if(!input.compare("ls")){
			char responseBuffer[256];
			int bytesRead = -1;
			bytesRead = recv(mySocket->mySocketFd, responseBuffer, sizeof(responseBuffer), 0);
			if(bytesRead == -1){
				cout << "Error reading server response..." << endl;
			}
			responseBuffer[bytesRead] = '\0';
			for(int i=0; i<bytesRead; i++){
				printf("%c",responseBuffer[i]);
			}
		}

		//Shutdown connection to be repopened on next iteration of loop
		shutdown(mySocket->mySocketFd, 2);
	}
}
