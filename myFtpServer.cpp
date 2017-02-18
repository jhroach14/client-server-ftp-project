#include "myFtpServer.h"

using namespace std;


//prints error message + errno and exits







int main( int argc, char *argv[]) {


	//stop children becoming zombies
	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
		cout << "Zombie stopped\n";
	}

	//ensure we get a port number
	if(argc !=2 ){
		cout << "Invalid server command. exiting\n";
		return -1;
	}

	Socket * mySock = new Socket((unsigned int) atoi(argv[1]));
	mySock->bindAndListen();

	//main server loop. Should run until it receives a kill signal from a child
	while(true){

		mySock->acceptConnectionFromClient();
		cout <<"Connection accpeted";
		
		string input = mySock->getInputFromClient();


		//Changes directory
		if(!input.compare(0,2,"cd")){
			mySock->sendOutputToClient("do cd")
		}
		
		int pId = fork(); //multi threading. RUN CODE ON CLUSTER unless forkbombing nike is desirable
		
		if(pId == 0){

				
			
			if(!input.compare("kill")){ //shutdown process
				if(kill(getppid(),-2)==-1){
					fatal_error("failed to kill parent");
				}
				return 0;
			}
			cout<<input;//just for debuging
			
			//command execution goes here
			
			// Redirects Standard output into socket then runs ls on server side
			if(!input.compare("ls"){
				
				dup2(mysock, STDOUT_FILENO);
				dup2(mysock, STDERR_FILENO);
				mySock->sendOutputToClient("do ls");
				system("ls");			
			}
			
			// Redirects STD Output into socket then runs pwd on server side
			if (!input.compare("pwd")){
				
				mySock->sendOutputToClient("do pwd");
				dup2(mysock, STDOUT_FILENO);
				dup2(mysock, STDERR_FILENO);
				system("pwd");
			}
			
			// Removes file
			if (!input.compare(0,3,"delete")){
				mySock->sendOutputToClient("do delete");

			}
			
			// makes new directory on FTP server
			if(!input.compare(0,5,"mkdir")){
				mySock->sendOutputToclient("do mkdir");

			}
			
			if(!input.compare(0,3,"get"){
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
			if(!input.compare(0,3,"get"){
				int index = input.find(" ");
				string fileName = input.substr(index);
				receiveFile = fopen(fileName.c_str(), "w");
				while((len = recv(mySocket->mySocketFd, mySocket->buffer, 256, 0) > 0)){
					fwrite(mySocket->buffer, sizeof(char), len, receiveFile);
				}
				fclose(receiveFile);
			}
			
		exit(0);
			
		}

	}
	mySock->shutDown();
	return 0;
}

