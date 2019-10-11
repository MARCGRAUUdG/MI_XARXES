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
 char miss[200];
 
 printf("Introdueix una IP: ");
 scanf("%s", IPRemot);
 
 printf("Introdueix un port (3678): ");
 scanf("%i", &portRemot);
 
 s1 = TCP_CreaSockClient("127.0.0.1",2000);
 TCP_DemanaConnexio(s1,IPRemot,portRemot);
 
 char IPloc[16]; 
 int portTCPloc;
 TCP_TrobaAdrSockLoc(s1, IPloc, portTCPloc);
 printf("Sock LOC: @IP %s,TCP, #port %i\n",IPloc,portTCPloc);
 char IPrem[16];
 int portTCPrem;
 TCP_TrobaAdrSockRem(s1, IPrem, portTCPrem);
 printf("Sock REM: @IP %s,TCP, #port %i\n",IPrem,portTCPrem); 
 
 while (miss[0]!='#')
 {
	  int llistaSck[1] = {s1};
	  if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) == 0)
	  {
		  TCP_Rep(0,miss,sizeof(miss));
	  } if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) >0)
	  {
		  TCP_Rep(s1,miss,sizeof(miss));
	  } if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) ==-1)
	  {
		  perror("EEEEEEEEEEEEEEEEEERROOOOOOOOOOOOOOR!");
	  }
	  TCP_Envia(s1,miss, sizeof(miss));
	  printf("%s\n", miss);
 }
 
 TCP_TancaSock(s1);
 
 return(0); 
} 
