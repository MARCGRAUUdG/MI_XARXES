#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
int main(int argc,char *argv[]) 
{ 
 int sesc, scon, i; 
 int bytes_llegits, bytes_escrits; 
 char buffer[200]; 
 int long_adrrem;
 struct sockaddr_in adrloc, adrrem; 
 char iploc[16]; 
 int portloc; 
 int s2=0;
                                                */ 
 TCP_CreaSockServidor("23.3.1.5,TCP,3678");
 TCP_AcceptaConnexio(s2,"88.8.12.3,TCP,2000");
 TCP_Rep(s2,"Com va això?");
 TCP_Rep(s2,"Estàs bé?");
 TCP_TancaSock(s2);
 
 return(0); 
} 
