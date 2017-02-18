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
	cout << "Server socket bound..." << endl;

	//main server loop. Should run until it receives a kill signal from a child
	while(true){

		mySock->acceptConnectionFromClient();
		cout <<"Connection accpeted";
		
		string input = mySock->getInputFromClient();
		cout << "input: " << input << " received.." << endl;


		
		int pId = fork(); //multi threading. RUN CODE ON CLUSTER unless forkbombing nike is desirable
		
		if(pId == 0){

			//Changes directory
			if(!input.compare(0,2,"cd")){
				int index = input.find(" ");
				string filepath = input.substr(index);
				chdir(filepath.c_str());
			}
			
			if(!input.compare("kill")){ //shutdown process
				if(kill(getppid(),-2)==-1){
					fatal_error("failed to kill parent");
				}
				return 0;
			}
			cout<<input;//just for debuging
			
			//command execution goes here
			
			// Redirects Standard output into socket then runs ls on server side
			if(!input.compare("ls")){
				cout << "Running ls..." << endl;
				dup2(mySock->mySocketFd, STDOUT_FILENO);
				dup2(mySock->mySocketFd, STDERR_FILENO);
				system("ls");			
			}
			
			// Redirects Standard output into socket then runs pwd on server side
			if (!input.compare("pwd")){
				dup2(mySock->mySocketFd, STDOUT_FILENO);
				dup2(mySock->mySocketFd, STDERR_FILENO);
				system("pwd");
			}
			
			// Removes file
			if (!input.compare(0,6,"delete")){
				int index = input.find(" ");
				string filepath = input.substr(index);
				string remove = "rm";
				remove.append(filepath);
				system(remove.c_str());
			}
			// makes new directory on FTP server
			if(!input.compare(0,5,"mkdir")){
				system(input.c_str());
			}
			//Client requests file
			if(!input.compare(0,3,"get")){
				int index = input.find(" ");
				string fileName = input.substr(index);
				FILE * sendFile = fopen(fileName.c_str(), "r");
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
			//Client putting file on server
			if(!input.compare(0,3,"put")){
				int index = input.find(" ");
				string fileName = input.substr(index);
				FILE * receiveFile = fopen(fileName.c_str(), "w");
				while((len = recv(mySocket->mySocketFd, mySocket->buffer, 256, 0) > 0)){
					fwrite(mySocket->buffer, sizeof(char), len, receiveFile);
				}
				fclose(receiveFile);
			}			
		}

	}
	mySock->shutDown();
	return 0;
}

