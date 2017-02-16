#include "myFtpServer.h"

using namespace std;

#define SOCKET_QUEUE 5 //max num of connections to que on socket

//prints error message + errno and exits
void fatal_error(string output){

	perror(strerror(errno));
	cout<<"\n"<<output<<'\n';
	exit(EXIT_FAILURE);

}

//just printout no exit
void error(string output){

	perror(strerror(errno));
	cout<<"\n"<<output<<'\n';

}

//below methods abstracts socket logic

//nitty gritty for socket creation
Socket::Socket(unsigned int portNo) {

	portNum = portNo;
	if((socketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		fatal_error("Socket creation Failed");
	}

	memset(&serverAddress, 0, sizeof( struct sockaddr_in));//set to zero
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY; //sets proper host IP
	serverAddress.sin_port = htons((uint16_t) portNum); // sets port

}
//initiates active socket
void Socket::bindAndListen(){
	//binds socket to port on host machine
	if (bind(socketFd, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr_in)) == -1) {
		fatal_error("Socket binding failed");
	}
	//initiates listening
	if (listen(socketFd, SOCKET_QUEUE) == -1) {
		fatal_error("Socket Listening Failed");
	}

}

//gets client connection
void Socket::acceptConnection(){

	if ((clientFd = accept(socketFd, (struct sockaddr *) &clientAddress, &clientLength) == -1)) {
		fatal_error("Client accept connection failed");
	}

}

//gets client input
string Socket::getInput(){

	memset(buffer, 0, 256);
	if(read(clientFd,buffer,255) == -1){
		fatal_error("Error reading input from client");
	}
	string strBuffer(buffer);
	return strBuffer;

}

//sends output to client
void Socket::toClient(string message){

	if(write(clientFd, message.c_str(),message.size())==-1){
		fatal_error("Error writing output to client");
	}

}

//does house keeping for server. Does not handle memory leaks
void Socket::shutDown() {

	if((close(socketFd))==-1){
		fatal_error("Error on socket close");
	}
	if((close(clientFd))==-1){
		fatal_error("Error on client close");
	}

}



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

		mySock->acceptConnection();

		int pId = fork(); //multi threading. RUN CODE ON CLUSTER unless forkbombing nike is desirable

		if(pId == 0){

			string input = mySock->getInput();

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

	return 0;
}


