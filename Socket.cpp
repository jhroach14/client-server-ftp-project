//#include <w32api/psdk_inc/_ip_types.h>
#include <sys/types.h>
#include "Socket.h"

//below methods abstracts socket logic

//nitty gritty for socket creation
Socket::Socket(unsigned int portNo) {

	portNum = portNo;
	if((mySocketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		fatal_error("Socket creation Failed");
	}

	memset(&myAddress, 0, sizeof( struct sockaddr_in));//set to zero
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY; //sets proper host IP
	myAddress.sin_port = htons((uint16_t) portNum); // sets port

}
//initiates active socket
void Socket::bindAndListen(){
	//binds socket to port on host machine
	if (bind(mySocketFd, (struct sockaddr *) &myAddress, sizeof(struct sockaddr_in)) == -1) {
		fatal_error("Socket binding failed");
	}
	//initiates listening
	if (listen(mySocketFd, SOCKET_QUEUE) == -1) {
		fatal_error("Socket Listening Failed");
	}

}

//gets client connection
void Socket::acceptConnectionFromClient(){

	if ((newSocketFd = accept(mySocketFd, (struct sockaddr *) &peerAddress, &socketLength) == -1)) {
		fatal_error("Client accept connection failed");
	}

}

//gets client input
string Socket::getInputFromClient(){

	memset(buffer, 0, 256);
	if(read(newSocketFd, buffer, 255) == -1){
		fatal_error("Error reading input from client");
	}
	string strBuffer(buffer);
	return strBuffer;

}

//sends output to client
void Socket::sendOutputToClient(string message){

	if(write(newSocketFd, message.c_str(), message.size()) == -1){
		fatal_error("Error writing output to client");
	}

}

string Socket::getInputFromServer(){

	memset(buffer, 0, 256);
	if(read(mySocketFd, buffer, 255) == -1){
		fatal_error("Error reading input from client");
	}
	string strBuffer(buffer);
	return strBuffer;

}

//sends output to client
void Socket::sendOutputToServer(string message){

	if(write(mySocketFd, message.c_str(), message.size()) == -1){
		fatal_error("Error writing output to client");
	}

}


void Socket::connectToServer(string domainName, int port) {

	if((server = gethostbyname(domainName.c_str())) == NULL){
		fatal_error("Invalid host name");
	}

	((char *) peerAddress->sin_addr->s_addr) = server->h_addr_list[0];
	peerAddress.sin_family = AF_INET;
	peerAddress.sin_port = htons((uint16_t) port);

	if (connect(mySocketFd, (struct sockaddr *) &peerAddress, sizeof(peerAddress)) == -1){
		fatal_error("Error on connectToServer");
	}

}
//does house keeping for server. Does not handle memory leaks
void Socket::shutDown() {

	if((close(mySocketFd)) == -1){
		fatal_error("Error on socket close");
	}
	if((close(newSocketFd)) == -1){
		fatal_error("Error on client close");
	}

}