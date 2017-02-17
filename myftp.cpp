#include "lib.h"
#include "Socket.h"

int main(int argc, char* argv[]){
	ssize_t len;
	FILE* sendFile;
	FILE* receiveFile;

	if(argc < 3){
		printf("Usage %s hostname port\n", argv[0]);
	}

	//Creates socket
	Socket * mySocket = new Socket((unsigned int)80);
	mySocket->connectToServer(argv[0], atoi(argv[1]));
	string input;

	//"Shell" loop
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
				sendFile = fopen(fileName.c_str(), "w");
				char* sendBuffer[256];
				fgets(buffer, 256, sendFile);
				int n = write(mySocketFd, sendBuffer, strlen(sendBuffer));
				if(n<0) cout << "Error writing file";
			}
		}
		else{
			mySocket->sendOutputToServer(input);
		}
		


	}
}
