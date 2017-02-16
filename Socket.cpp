//
// Created by User on 2/16/2017.
//

#include "Socket.h"

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