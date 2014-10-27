/*
CS436
Gilbert Duenas
Project 01 Socket programming

Server implementation
*/

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define BUFFSIZE 8192
#define SA struct sockaddr

using namespace std;

const int backlog = 4;

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

// To be implemented

/*
void *clientHandler(void *arg)
{
  char str[MAXLINE];
  int  fd = *(int*)(arg);
  int  input;

  while(1)
  {
    if((input = read(fd, str, MAXLINE)) == 0)
    {
      close (fd);
      return 0;
    }
    for(int i = 0; i < strlen(str); i++) 
    {
      if(str[i] >= 97 && str[i] <= 122) 
      {
        str[i] = str[i] - 32;
      }
    }
    write(fd, str, strlen(str));
  }
}
*/

void getClient(int socketInput)
{
  char buffer[256];
  int input;

  bzero(buffer,256);
  input = read(socketInput,buffer,255);
  
  if (input < 0) 
  {
    error("Cannot read socket");
  }

  input = write(socketInput,"> ",18);
  cout << "Received: " << input << endl;
  
  if(input < 0)
  {
    error("Cannot write to socket");
  }
}

int main(int argc, char *argv[])
{
  int sockFD, createSockFD, portNum, pid;
  socklen_t clientLength;
  struct sockaddr_in serverAddress, clientAddress;

  if(argc < 2) 
  {
    cout << "Please enter a port number." << endl;
    exit(1);
  }

  sockFD = socket(AF_INET, SOCK_STREAM, 0);

  if(sockFD < 0) 
  {
    error("Cannot open socket");
  }

  cout << "Waiting for connection...." << endl;
  bzero((char *) &serverAddress, sizeof(serverAddress));
  portNum = atoi(argv[1]);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(portNum);

  if(bind(sockFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) 
  {
    error("Cannot bind socket");
  }

  listen(sockFD, 5);
  clientLength = sizeof(clientAddress);

  while(1) 
  {
    createSockFD = accept(sockFD, (struct sockaddr *) &clientAddress, &clientLength);
    
    if (createSockFD < 0) 
    {
      error("Cannot accept socket");
    }

    cout << "Client connecting...." << endl;
    pid = fork();

    if(pid < 0)
    {
      error("Cannot fork process");
    }

    if(pid == 0)
    {
      close(sockFD);
      getClient(createSockFD);
      exit(0);
    }
    else 
    {
      close(createSockFD);
    }
  }
  close(sockFD);
}
