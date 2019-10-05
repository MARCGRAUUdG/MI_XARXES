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
 int s2=0, aux_s2=0;
 int portRemot;
 char miss[200];
 miss[0] = ' ';
 char IPRemot[20];

 struct sockaddr_in adrl;
 int long_adrl;
 struct sockaddr_in adrr;
 int long_adrr;

 
 printf("Introdueix una IP: ");
 scanf("%s", IPRemot);
 
 printf("Introdueix un port (2000): ");
 scanf("%i", &portRemot);
 
 s2 = TCP_CreaSockServidor("127.0.0.1",3678);
 aux_s2 = TCP_AcceptaConnexio(s2,IPRemot,&portRemot);
 
 long_adrl = sizeof(adrl);  
 if (getsockname(aux_s2, (struct sockaddr *)&adrl, &long_adrl) == -1)  
 {    perror("Error en getsockname");   close(aux_s2);   exit(-1);  }
 printf("Sock LOC: @IP %s,TCP, #port %d\n",inet_ntoa(adrl.sin_addr),ntohs(adrl.sin_port));

 long_adrr = sizeof(adrr);
 if (getpeername(aux_s2, (struct sockaddr *)&adrr, &long_adrr) == -1)  
 {    perror("Error en getpeername");   close(aux_s2);   exit(-1);  }
 printf("Sock REM: @IP %s,TCP, #port %d\n",inet_ntoa(adrr.sin_addr),ntohs(adrr.sin_port)); 
                                            
 while (miss[0]!='#')
 {
	 TCP_Rep(aux_s2,miss,sizeof(miss));
	 printf("%s\n", miss);
 }
 
 TCP_TancaSock(s2);
 TCP_TancaSock(aux_s2);
 
 return(0); 
} 
