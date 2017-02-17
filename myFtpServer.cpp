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
		
		
		string input = mySock->getInputFromClient();
		char  *argv[16];
		getArguments(input, argv);

		//Changes directory
		if(!input.compare(0,2,"cd")){
			mySock->sendOutputToClient("do cd")
			chdir(argv[1]);
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
				execvp(*argv, argv);				
			}
			
			// Redirects STD Output into socket then runs pwd on server side
			if (!input.compare("pwd")){
				
				mySock->sendOutputToClient("do pwd");
				dup2(mysock, STDOUT_FILENO);
				dup2(mysock, STDERR_FILENO);
				execvp(*argv, argv);
			}
			
			// Removes file
			if (!input.compare(0,3,"delete")){
				mySock->sendOutputToClient("do delete");
				*argv[0] = "rm";
				execvp(*argv, argv);
			}
			
			// makes new directory on FTP server
			if(!input.compare(0,5,"mkdir")){
				mySock->sendOutputToclient("do mkdir");
				execvp(*argv, argv);
			}
			
		exit(0);
			
		}

	}
	mySock->shutDown();
	return 0;
}

/**
   Breaks input down into arrays to be used by exec()
**/
void  getArguments(string line, char **argv){
	size_t found = input.find(" ");
	if(found != string::npos){
      inf index = input.find(" ");
	  line.copy(*argv[0],0,index-1)
	  line.copy(*argv[1],index,line.length());
	  *argv[2] = NULL;
    }else{
		line.copy(*argv[0],0,line.length());
		*argv[1] = NULL;
	}
}


