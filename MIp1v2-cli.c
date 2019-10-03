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
 int scon, i; 
 int bytes_llegits, bytes_escrits; 
 char buffer[200]; 
 struct sockaddr_in adrrem; 
 char iprem[16]; 
 int portrem; 
 int s1=0;
 /* Es crea el socket TCP scon del client (el socket "local"), que de moment no té       */ 
 /* adreça (@IP i #port TCP) assignada.                                                  */ 
 
 TCP_CreaSockClient("88.8.12.3,TCP,2000");
 TCP_DemanaConnexio(s1,"23.3.1.5,TCP,3678");
 TCP_Envia(s1,"Com va això?");
 TCP_Envia(s1,"Estàs bé?");
 TCP_TancaSock(s1);
 
 return(0); 
} 
