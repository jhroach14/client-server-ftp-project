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

		int pId = fork(); //multi threading. RUN CODE ON CLUSTER unless forkbombing nike is desirable

		if(pId == 0){

			string input = mySock->getInputFromClient();

			if(!input.compare("kill")){ //shutdown process
				if(kill(getppid(),-2)==-1){
					fatal_error("failed to kill parent");
				}
				return 0;
			}
			cout<<input;//just for debuging
			
			//command execution goes here
			
			// Creates temp file that stores ls data then sends to client
			if(!input.compare("ls"){
				mySock->sendOutputToClient("do ls");
				system("ls > temp");
				sendFile = fopen("temp", "r");
				int size = ftell("temp");
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
				system("rm temp");
				
			}
			
			
		}

	}
	mySock->shutDown();
	return 0;
}


