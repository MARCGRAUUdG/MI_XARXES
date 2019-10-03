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
                                                
 s2 = TCP_CreaSockServidor("23.3.1.5",3678);
 TCP_AcceptaConnexio(s2,"88.8.12.3",&port);
 TCP_Rep(s2,"Com va això?",sizeof("Com va això?"));
 TCP_Rep(s2,"Estàs bé?",sizeof("Estàs bé?"));
 TCP_TancaSock(s2);
 
 return(0); 
} 
