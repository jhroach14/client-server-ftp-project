//
// Created by User on 2/16/2017.
//

#include "lib.h"

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
