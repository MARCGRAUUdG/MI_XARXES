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
 char IPRemot[20];
 int portRemot;
 
 struct sockaddr_in adrl;
 int long_adrl;
 struct sockaddr_in adrr;
 int long_adrr;
 char missatge_enviar[200];
 
 printf("Introdueix una IP: ");
 scanf("%s", IPRemot);
 
 printf("Introdueix un port (3678): ");
 scanf("%i", &portRemot);
 
 s1 = TCP_CreaSockClient("127.0.0.1",2000);
 TCP_DemanaConnexio(s1,IPRemot,portRemot);
 
  long_adrl = sizeof(adrl);  
 if (getsockname(s1, (struct sockaddr *)&adrl, &long_adrl) == -1)  
 {    perror("Error en getsockname");   close(s1);   exit(-1);  }
 printf("Sock LOC: @IP %s,TCP, #port %d\n",inet_ntoa(adrl.sin_addr),ntohs(adrl.sin_port));

 long_adrr = sizeof(adrr);
 if (getpeername(s1, (struct sockaddr *)&adrr, &long_adrr) == -1)  
 {    perror("Error en getpeername");   close(s1);   exit(-1);  }
 printf("Sock REM: @IP %s,TCP, #port %d\n",inet_ntoa(adrr.sin_addr),ntohs(adrr.sin_port)); 
 
 while (missatge_enviar[0]!='#')
 {
	 scanf("%s", missatge_enviar);
	 TCP_Envia(s1,missatge_enviar, sizeof(missatge_enviar));
 }
 
 TCP_TancaSock(s1);
 
 return(0); 
} 
