#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#define PORT 8080

using namespace std;

void moveClient(){
  char buffer[128];
  string cmd = string("sh exec.sh");
  string result = "";
  FILE* pipe = popen(cmd.c_str(),"r");
  if(!pipe)
    try{
      while(fgets(buffer,sizeof buffer, pipe)!=NULL){
        result += buffer;
      }
    } catch(...){
      pclose(pipe);
      throw;
    }
  pclose(pipe);
  cout << result << endl;
}

int main(int argc, char const *argv[]) 
{ 
  int server_fd, new_socket, valread; 
  struct sockaddr_in address; 
  int opt = 1; 
  int addrlen = sizeof(address); 
  char buffer[1024] = {0}; 
  char *hello = "Hello from server"; 

  // Creating socket file descriptor 
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
  { 
    perror("socket failed"); 
    exit(EXIT_FAILURE); 
  } 

  // Forcefully attaching socket to the port 8080 
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
        &opt, sizeof(opt))) 
  { 
    perror("setsockopt"); 
    exit(EXIT_FAILURE); 
  } 
  address.sin_family = AF_INET; 
  address.sin_addr.s_addr = INADDR_ANY; 
  address.sin_port = htons( PORT ); 

  // Forcefully attaching socket to the port 8080 
  if (bind(server_fd, (struct sockaddr *)&address,  
        sizeof(address))<0) 
  { 
    perror("bind failed"); 
    exit(EXIT_FAILURE); 
  } 
  if (listen(server_fd, 3) < 0) 
  { 
    perror("listen"); 
    exit(EXIT_FAILURE); 
  } 
  while ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
          (socklen_t*)&addrlen))>0) 
  {
    if(new_socket == -1){
      perror("accept"); 
      continue;
    }
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 

    moveClient();

    pid_t pid = fork();
    if(pid==0){
      printf("Exec DR\n");
      execl("bin64/drrun", "drrun", "-root", "/system/build_android","-c", "api/bin/libmyclient.so", "--", "mybinary",NULL);
    }
    else {
      wait(NULL);
    }

    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
  }
  return 0; 
}
