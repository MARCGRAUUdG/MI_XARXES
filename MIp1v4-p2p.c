/**************************************************************************/
/*                                                                        */
/* P1 - MI amb sockets TCP/IP - Part I                                    */
/* Fitxer p2p.c que implementa la interfície aplicació-usuari de          */
/* l'aplicació de MI, sobre la capa d'aplicació de MI (fent crides a la   */
/* interfície de la capa MI -fitxers mi.c i mi.h-).                       */
/* Autors: Marc Grau i Xavier Roca                                                          */
/*                                                                        */
/**************************************************************************/


/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */
/* Incloem "MIp1v4-mi.h" per poder fer crides a la interfície de MI       */
#include "MIp1v2-t.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include "MIp1v2-t.h"

/* Definició de constants, p.e., #define XYZ       1500                   */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les seves definicions es troben més avall) per així fer-les conegudes */
/* des d'aqui fins al final de fitxer.                                    */

/* Funció main()                                                          */

int main(int argc,char *argv[])
{
	int midaMiss;
	int sesc=0, scon=0;
	int ipServidor;
	int portServidor;
	int portRemot;
	char miss[200];
	miss[0] = ' ';
	char IPRemot[20];
	char nickLoc[200], nickRem[200];

	printf("Escriu el teu nick:\n ");  //S'HA DE CODIFICAR EL NICK
	int aux_nickLoc = read(0, nickLoc, sizeof(nickLoc));
	
	
	printf("Escriu el port del socket servidor:\n ");  //S'HA DE CODIFICAR EL NICK
	scanf("%d", &portServidor);
	 
	if((sesc = TCP_CreaSockServidor("192.168.43.40", portServidor)) == -1){
		T_MostraError();
		return -1;
	}
		
	printf("Introdueix la IP a on et vols connectar:\n ");
	
	int llistaSck[2];
	llistaSck[0] = 0;
	llistaSck[1] = sesc;

	int ha_arribat = T_HaArribatAlgunaCosa(llistaSck, 2);

	if(ha_arribat == -1){
		perror("Error, a l'arribar alguna cosa");
		return -1;
	}
	if (ha_arribat == 0) {printf("%s", "he emtrat 0\n");
		scanf("%s", IPRemot);
				
		printf("Introdueix el port al que et vols connectar:\n");
		scanf("%d", &portRemot);
		
		if ((scon = TCP_CreaSockClient("0.0.0.0", 0)) == -1){
			T_MostraError();
			return -1;
		}
		
		
		if (TCP_DemanaConnexio(scon, IPRemot, portRemot) == -1){
			T_MostraError();
			return -1;
		}
		
		if (TCP_Envia(scon, nickLoc, strlen(nickLoc)) == -1) {
			T_MostraError();
			return -1;
		}
		
		if (TCP_Rep(scon, nickRem, 200) == -1) {
			T_MostraError();
			return -1;
		}	
	}
	else {
		
		if((scon = TCP_AcceptaConnexio(sesc, IPRemot, &portRemot)) == -1){
			T_MostraError();
			return -1;
		}


		if(TCP_Rep(scon, nickRem, 200) == -1){
			T_MostraError();
			return -1;
		}

		if(TCP_Envia(scon, nickLoc, strlen(nickLoc)) == -1){
			T_MostraError();
			return -1;
		}
	}
		
	printf("%s i %s s'han connectat correctament...\n", nickLoc, nickRem);
	printf("Començem a xatejar:\n");
	
	do{
		int llistaSck[2];
		llistaSck[0] = 0;
		llistaSck[1] = scon;

		ha_arribat = T_HaArribatAlgunaCosa(llistaSck, 2);
		printf("socket on ha arribat algo: %d", ha_arribat);
		if (ha_arribat == 0) //Envia missatge
		{
		  printf("Estic donant\n");
		  midaMiss = read(0, miss, sizeof(miss));
		  miss[midaMiss-1] = '\0';
		  
		  if (miss[0] == '#')
		  {
			  printf("T'has desconnectat");
		  } else
		  {
			  //printf("%s\n", nickLoc);
			  if (TCP_Envia(scon, miss, strlen(miss)) == -1)
			  {
				  perror("Error");
				  exit(-1);
			  }
		  }
		} else //rep missatge
		{
			printf("Estic rebent\n");
			midaMiss = TCP_Rep(scon, miss, sizeof(miss));
			printf("Mida del missatge: %d\n", midaMiss);
			if (midaMiss == -1) {exit(-1);}
			else if (midaMiss == 0) printf("L'usuari s'ha desconectat");
			else
			{
				//printf("%s\n", nickRem);
				printf("Missatge: %s\n", miss);
			}
		}
		
	} while (midaMiss!=0 && miss[0]!='#');	
	
	TCP_TancaSock(llistaSck[1]);
	
 
	return(0); 
 }
