/*
CS436
Gilbert Duenas
Project 01 Socket programming

Client implementation

1. Initial Client log in
====================
Implemented
------------------
The program should prompt the user to enter his username when connected to the server.

NOT Implemented
------------------------
If the username has already been taken, the server prompts the user to enter another username. 
If the username has NOT been taken, the server then stores the information (username, client socket descriptor, and IP address) of the client. 
The information of the clients can be stored in a file at the server.

2. Successful login
=================
Implemented
------------------
After successful login, the following menu should be displayed in the client’s console:

3. List - NOT Implemented

4. Chat - NOT Implemented

5. Exit - NOT Implemented

6. Client to client chatting - NOT Implemented

7. Message Structure - NOT Implemented
*/

#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netdb.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 256

using namespace std; 

void error(const char *msg)
{
  perror(msg);
  exit(0);
}

// To be implemented

/*void str_client(FILE *fp, int socketFD)
{
  char	sendMsg[MAXLINE];
  char	receiveMsg[MAXLINE];

  memset((void *)sendMsg, 0, MAXLINE);
  memset((void *)receiveMsg, 0, MAXLINE);

  if(fgets(sendMsg, MAXLINE, fp) != NULL) 
  {
    write(socketFD, (void *)sendMsg, strlen(sendMsg));

    if(read(socketFD, receiveMsg, MAXLINE) == 0) 
    {
      cout << "Server exiting...." << endl;
      return;
    }
    fputs(receiveMsg, stdout);
  }
}*/

int main(int argc, char *argv[])
{
  char buffer[256];
  int choice;
  int input;
  int portNum; 
  int socketFD;

  struct hostent *server;
  struct sockaddr_in serv_addr;

  if(argc < 3) 
  {
    cout << "Please enter host address and port number." << endl;
    exit(0);
  }

  portNum = atoi(argv[2]);
  socketFD = socket(AF_INET, SOCK_STREAM, 0);

  if(socketFD < 0) 
  {
    error("ERROR opening socket");
  }

  server = gethostbyname(argv[1]);

  if(server == NULL) 
  {
    cout << "Host does not exist" << endl;
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
  (char *)&serv_addr.sin_addr.s_addr,
  server->h_length);
  serv_addr.sin_port = htons(portNum);

  if(connect(socketFD,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
  {
    error("Cannot connect.");
  }

  //The program should prompt the user to enter his username when connected to the server.
  cout << "Please enter your name: " << endl;
  bzero(buffer,256);
  fgets(buffer,255,stdin);
  input = write(socketFD,buffer,strlen(buffer));

  if(input < 0) 
  {
    error("Cannot write to socket");
  }

  bzero(buffer,256);
  input = read(socketFD,buffer,255);

  if (input < 0) 
  {
    error("Cannot read socket");
  }

  //After successful login, the following menu should be displayed in the client’s console:
  while(1)
  {
    cout << "\n1. List users\n"
    << "2. Chat\n"
    << "3. Exit\n"
    << "Enter your choice: " << endl;  
    cin >> choice;
    
    switch(choice)
    {
    case 1:
      break;
    case 2:
      break;
    case 3:
       cout << "Closing connection....\n"
       << "....\n"
       << "....\n"
       << "Goodbye." << endl;
      close(socketFD);
      return 0;
    default:
      cout << "Please enter a valid selection." << endl;
      break;
    }
  }
}
