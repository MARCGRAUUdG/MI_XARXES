#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include "MIp1v2-t.h"
int main(int argc,char *argv[]) 
{ 
 int s2=0;
 int port = 2000;
 char miss[200];
                                                
 s2 = TCP_CreaSockServidor("127.0.0.1",3678);
 TCP_AcceptaConnexio(s2,"127.0.0.1",&port);
 TCP_Rep(s2,miss,sizeof(miss));
 TCP_TancaSock(s2);
 
 return(0); 
} 
