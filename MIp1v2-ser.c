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

 
 printf("Introdueix una IP: ");
 scanf("%s", IPRemot);
 
 printf("Introdueix un port (2000): ");
 scanf("%i", &portRemot);
 
 s2 = TCP_CreaSockServidor("127.0.0.1",3678);
 aux_s2 = TCP_AcceptaConnexio(s2,IPRemot,&portRemot);
 
 char *IPloc, int *portTCPloc;
 TCP_TrobaAdrSockLoc(aux_s2, IPloc, portTCPloc);
 printf("Sock LOC: @IP %s,TCP, #port %d\n",IPloc,portTCPloc);
 char *IPrem, int *portTCPrem;
 TCP_TrobaAdrSockRem(aux_s2, IPrem, portTCPrem);
 printf("Sock REM: @IP %s,TCP, #port %d\n",IPrem,portTCPrem); 

                                             
 while (miss[0]!='#')
 {
	  int llistaSck[1] = aux_s2;
	  if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) == 0)
	  {
		  TCP_Rep(0,miss,sizeof(miss));
	  } else if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) >0)
	  {
		  TCP_Rep(aux_s2,miss,sizeof(miss));
	  } else
	  {
		  perror("EEEEEEEEEEEEEEEEEERROOOOOOOOOOOOOOR!")
	  }
	 
	  printf("%s\n", miss);
 }
 
 TCP_TancaSock(s2);
 TCP_TancaSock(aux_s2);
 
 return(0); 
} 
