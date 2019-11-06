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
	int sesc=0, scon=0;
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
	
	//AQUI ESPERA UN INTRO --> SOLUCIONAR!
	 
	if((sesc = TCP_CreaSockServidor("127.0.0.1", portServidor)) == -1){
		T_MostraError();
		return -1;
	}
		
	printf("Introdueix la IP a on et vols connectar: ");
	
	
	int llistaSck[2];
	llistaSck[0] = 0;
	llistaSck[1] = sesc;

	int ha_arribat = T_HaArribatAlgunaCosa(llistaSck, 2);

	if(ha_arribat == -1){
		perror("Error, a l'arribar alguna cosa");
		return -1;
	}
	if (ha_arribat == 0) {
		scanf("%s", IPRemot);
		//printf("%s", IPRemot);
		
		printf("Introdueix el port al que et vols connectar: ");
		scanf("%d", &portRemot);
		
		if ((scon = TCP_CreaSockClient("0.0.0.0", 0)) == -1){
			T_MostraError();
			return -1;
		}
		
		if (TCP_DemanaConnexio(scon, IPRemot, portRemot) == -1){
			T_MostraError();
			return -1;
		}
		
		printf("%s", "He demanat connexió");
		
		if (TCP_Envia(scon, nickLoc, strlen(nickLoc)) == -1) {
			T_MostraError();
			return -1;
		}
		
		if (TCP_Rep(scon, nickRem, 200) == -1) {
			T_MostraError();
			return -1;
		}
		//llistaSck[1] = sck;	
		printf("%s", "He demanat connexió");
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
		//llistaSck[1] = sckRem;
		printf("%s", "He acceptat connexió");
	}
		
	printf("%s i %s s'han connectat correctament...", nickLoc, nickRem);
	printf("Començem a xatejar:");
	
	
	while (miss[0]!='#'){
		if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) == 0)
		{
		  TCP_Rep(0,miss,sizeof(miss));
		  TCP_Envia(llistaSck[1],miss, sizeof(miss));
		} 
		if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) >0)
		{
		  TCP_Rep(llistaSck[1],miss,sizeof(miss));
		  printf("%s\n", miss);
		} 
		if (T_HaArribatAlgunaCosa(llistaSck, sizeof(llistaSck)) ==-1)
		{
		  perror("Error, no s'ha rebut/enviat correctament el missatge");
		}
	}	
	
	TCP_TancaSock(llistaSck[1]);
	
 
	return(0); 
 }
