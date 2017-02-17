

#ifndef SERVER_CLIENT_LIB_H
#define SERVER_CLIENT_LIB_H

#include <iostream>
#include <string>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <stdbool.h>
#include <cstdio>
#include <signal.h>
#include <netdb.h>
#include "Socket.h"

#define SOCKET_QUEUE 5 //max num of connections to que on socket


using namespace std;

void fatal_error(string output);
void error(string output);


#endif //SERVER_CLIENT_LIB_H
