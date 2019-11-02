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
	int sck=0, aux_s=0;
	int portRemot;
	char miss[200];
	miss[0] = ' ';
	char IPRemot[20];
	char nickLoc[200], nickRem[200];

	printf("Escriu el teu nick:\n ");  //S'HA DE CODIFICAR EL NICK
	int aux_nickLoc = read(0, nickLoc, sizeof(nickLoc));
	 
	if((sck = TCP_CreaSockServidor("127.0.0.1",0)) == -1){
		T_MostraError();
		return -1;
	}
	
	//printf("%i", sck);

	printf("Introdueix la IP a on et vols connectar: ");
	 
	int llistaSck[2];
	llistaSck[0] = 0;
	llistaSck[1] = sck;

	if(T_HaArribatAlgunaCosa(llistaSck, 2) == -1){
	perror("Error, a l'arribar alguna cosa");
	return -1;
	}
	else{
		if (T_HaArribatAlgunaCosa(llistaSck, 2) == 0){
			scanf("%s", IPRemot);
			//printf("%s", IPRemot);
			
			printf("Introdueix el port al que et vols connectar: ");
			scanf("%i", &portRemot);
			
			printf("%i", portRemot);
			int sckLoc;
			if ((sckLoc = TCP_CreaSockClient("0.0.0.0", 0)) == -1){
				perror("Error al crear el scoket local");
				return -1;
			}
			
			if (TCP_DemanaConnexio(sckLoc, IPRemot, portRemot) == -1){
				perror("Error, al connectar al socket remot");
				return -1;
			}
			
			if (TCP_Envia(sckLoc, nickLoc, strlen(nickLoc)) == -1) {
				perror ("Error a l'enviar el nick");
				return -1;
			}
			
			if (TCP_Rep(sckLoc, nickRem, 200) == -1) {
				perror ("Error al rebre el nick remot");
				return -1;
			}
			llistaSck[1] = sck;	
			printf("%s", "He demanat connexió");
		}
		else{
			
			int sckRem;
			if((sckRem = TCP_AcceptaConnexio(sck, IPRemot, &portRemot)) == -1){
				perror("Error a l'acceptar la connexió");
				return -1;
			}
	

			if(TCP_Rep(sckRem, nickRem, 200) == -1){
				perror("Error al rebre el nick remot");
				return -1;
			}

			if(TCP_Envia(sckRem, nickLoc, strlen(nickLoc)) == -1){
				perror("Error a l'enviar el nick");
				return -1;
			}
			llistaSck[1] = sckRem;
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
	}
	 
		return(0); 
 }
