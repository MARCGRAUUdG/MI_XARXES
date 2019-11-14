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
#include "MIp1v4-mi.h"

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
	int portLocal;
	char miss[200];
	miss[0] = ' ';
	char IPRemot[20];
	char IPLocal[20];
	char nickLoc[200], nickRem[200];

	printf("Escriu el teu nick:\n ");  //S'HA DE CODIFICAR EL NICK
	int aux_nickLoc = read(0, nickLoc, sizeof(nickLoc));
	nickLoc[aux_nickLoc-1] = '\0';
	
	printf("Escriu el port del socket servidor:\n ");  //S'HA DE CODIFICAR EL NICK
	scanf("%d", &portServidor);
	 
	sesc = MI_IniciaEscPetiRemConv(portServidor);
	
	printf("Sesc: %d", sesc);
		
	printf("Introdueix la IP a on et vols connectar:\n ");
	
	int ha_arribat = MI_HaArribatPetiConv(sesc);
	
	if(ha_arribat == -1)
	{
		perror("Error, a l'arribar alguna cosa");
		return -1;
	}
	else if (ha_arribat == 0) 
	{
		scanf("%s", IPRemot);
				
		printf("Introdueix el port al que et vols connectar:\n");
		scanf("%d", &portRemot);
		printf("arribo");
		scon = MI_DemanaConv(IPRemot, portRemot, IPLocal, &portLocal, nickLoc, nickRem);
		
	}
	else {
		scon = MI_AcceptaConv(sesc, IPRemot, &portRemot, IPLocal, &portLocal, nickLoc, nickRem);
	}
		
	printf("%s i %s s'han connectat correctament...\n", nickLoc, nickRem);
	printf("Començem a xatejar:\n");
	
	do{
		ha_arribat = MI_HaArribatLinia(scon);
		if (ha_arribat == 0) //Envia missatge
		{
		  midaMiss = read(0, miss, sizeof(miss));
		  miss[midaMiss-1] = '\0';
		  
		  if (miss[0] == '#')
		  {
			  printf("T'has desconnectat");
		  } else
		  {
			  printf("%s\n", nickLoc);
			  midaMiss = MI_EnviaLinia(scon, miss);
		  }
		} else //rep missatge
		{
			midaMiss = MI_RepLinia(scon, miss);
			//printf("Mida del missatge: %d\n", midaMiss);
			if (midaMiss == -1) {exit(-1);}
			/*else if (midaMiss == 0) printf("L'usuari s'ha desconectat");*/
			else
			{
				printf("%s\n", nickRem);
				printf("Missatge: %s\n", miss);
			}
		}
		
	} while (/*midaMiss!=0 &&*/ miss[0]!='#');	
	
	MI_AcabaConv(scon);
	
 
	return(0); 
 }
