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
	cout << "creating Socket" <<endl;
	Socket * mySock = new Socket((unsigned int) atoi(argv[1]));
	cout << "SOCKET CREATED ON PORT " << argv[1];
	mySock->bindAndListen();

	//main server loop. Should run until it receives a kill signal from a child
	while(true){
		cout << "entering loop..." << endl;
		mySock->acceptConnectionFromClient();
		cout << "CONNECTION ACCEPTED";
		int pId = fork(); //multi threading. RUN CODE ON CLUSTER unless forkbombing nike is desirable

		if(pId == 0){

			string input = mySock->getInputFromClient();

			if(input.compare("kill")){ //shutdown process
				if(kill(getppid(),-2)==-1){
					fatal_error("failed to kill parent");
				}
				return 0;
			}
			cout<<input;//just for debuging

			//command execution goes here

		}

	}
	mySock->shutDown();
	return 0;
}


