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
 int s1=0;
 
 s1 = TCP_CreaSockClient("127.0.0.1",2000);
 TCP_DemanaConnexio(s1,"127.0.0.1",3678);
 TCP_Envia(s1,"Com va això?", sizeof("Com va això?"));
 TCP_TancaSock(s1);
 
 return(0); 
} 
