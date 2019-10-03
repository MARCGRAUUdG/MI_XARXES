/**************************************************************************/
/*                                                                        */
/* P1 - MI amb sockets TCP/IP - Part I                                    */
/* Fitxer t.c que "implementa" la capa de transport, o més ben dit, que   */
/* encapsula les funcions de la interfície de sockets, en unes altres     */
/* funcions més simples i entenedores: la "nova" interfície de sockets.   */
/* Autors: X, Y                                                           */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <sys/types.h> o #include "meu.h" */
/*  (si les funcions externes es cridessin entre elles, faria falta fer   */
/*   un #include del propi fitxer .h)                                     */
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

/* Definició de constants, p.e., #define XYZ       1500                   */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les seves definicions es troben més avall) per així fer-les conegudes */
/* des d'aqui fins al final de fitxer.                                    */

/* Definicio de funcions EXTERNES, és a dir, d'aquelles que en altres     */
/* fitxers externs es faran servir.                                       */
/* En termes de capes de l'aplicació, aquest conjunt de funcions externes */
/* són la "nova" interfície de la capa de transport (la "nova" interfície */
/* de sockets).                                                           */

/* Crea un socket TCP “client” a l’@IP “IPloc” i #port TCP “portTCPloc”   */
/* (si “IPloc” és “0.0.0.0” i/o “portTCPloc” és 0 es fa/farà una          */
/* assignació implícita de l’@IP i/o del #port TCP, respectivament).      */
/* "IPloc" és un "string" de C (vector de chars imprimibles acabat en     */
/* '\0') d'una longitud màxima de 16 chars (incloent '\0').               */
/* Retorna -1 si hi ha error; l’identificador del socket creat si tot     */
/* va bé.                                                                 */
int TCP_CreaSockClient(const char *IPloc, int portTCPloc)
{
	int scon;
	
	if((scon=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{ 
		perror("Error en socket"); 
		exit(-1);
	}
	
	return scon;
}

/* Crea un socket TCP “servidor” (o en estat d’escolta – listen –) a      */
/* l’@IP “IPloc” i #port TCP “portTCPloc” (si “IPloc” és “0.0.0.0” i/o    */
/* “portTCPloc” és 0 es fa una assignació implícita de l’@IP i/o del      */
/* #port TCP, respectivament).                                            */
/* "IPloc" és un "string" de C (vector de chars imprimibles acabat en     */
/* '\0') d'una longitud màxima de 16 chars (incloent '\0').               */
/* Retorna -1 si hi ha error; l’identificador del socket creat si tot     */
/* va bé.                                                                 */
int TCP_CreaSockServidor(const char *IPloc, int portTCPloc)
{
	int sesc, i;
	struct sockaddr_in adrloc;
	
	if((sesc=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		return -1;
	}
	 
	 adrloc.sin_family=AF_INET; 
	 adrloc.sin_port=htons(portTCPloc); 
	 adrloc.sin_addr.s_addr=inet_addr(IPloc);    /* o bé: ...s_addr = INADDR_ANY */ 
	 for(i=0;i<8;i++){adrloc.sin_zero[i]='\0';} 
	 if((bind(sesc,(struct sockaddr*)&adrloc,sizeof(adrloc)))==-1) 
	 { 
	  perror("Error en bind"); 
	  close(sesc); 
	  exit(-1); 
	 } 
	
	 if((listen(sesc,3))==-1) 
	 { 
	  perror("Error en listen"); 
	  close(sesc); 
	  exit(-1); 
	 } 
	 
	 return sesc;
}

/* El socket TCP “client” d’identificador “Sck” es connecta al socket     */
/* TCP “servidor” d’@IP “IPrem” i #port TCP “portTCPrem” (si tot va bé    */
/* es diu que el socket “Sck” passa a l’estat “connectat” o establert     */
/* – established –). Recordeu que això vol dir que s’estableix una        */
/* connexió TCP (les dues entitats TCP s’intercanvien missatges           */
/* d’establiment de la connexió).                                         */
/* "IPrem" és un "string" de C (vector de chars imprimibles acabat en     */
/* '\0') d'una longitud màxima de 16 chars (incloent '\0').               */
/* Retorna -1 si hi ha error; un valor positiu qualsevol si tot va bé.    */
int TCP_DemanaConnexio(int Sck, const char *IPrem, int portTCPrem)
{
	 int i;
	 struct sockaddr_in adrrem;
	 
	 adrrem.sin_family=AF_INET; 
	 adrrem.sin_port=htons(portTCPrem); 
	 adrrem.sin_addr.s_addr= inet_addr(IPrem); 
	 for(i=0;i<8;i++){adrrem.sin_zero[i]='\0';} 
	 if((connect(Sck,(struct sockaddr*)&adrrem,sizeof(adrrem)))==-1) 
	 { 
	  perror("Error en connect"); 
	  close(Sck); 
	  exit(-1); 
	 } 
	 return 0;
}

/* El socket TCP “servidor” d’identificador “Sck” accepta fer una         */
/* connexió amb un socket TCP “client” remot, i crea un “nou” socket,     */
/* que és el que es farà servir per enviar i rebre dades a través de la   */
/* connexió (es diu que aquest nou socket es troba en l’estat “connectat” */
/* o establert – established –; el nou socket té la mateixa adreça que    */
/* “Sck”).                                                                */
/* Omple “IPrem*” i “portTCPrem*” amb respectivament, l’@IP i el #port    */
/* TCP del socket remot amb qui s’ha establert la connexió.               */
/* "IPrem*" és un "string" de C (vector de chars imprimibles acabat en    */
/* '\0') d'una longitud màxima de 16 chars (incloent '\0').               */
/* Retorna -1 si hi ha error; l’identificador del socket connectat creat  */
/* si tot va bé.                                                          */
int TCP_AcceptaConnexio(int Sck, char *IPrem, int *portTCPrem)
{
	int scon;
	struct sockaddr_in adrrem; 
	 
	int long_adrrem=sizeof(adrrem); 
	 if((scon=accept(Sck,(struct sockaddr*)&adrrem, &long_adrrem))==-1) 
	 { 
	  perror("Error en accept"); 
	  close(Sck); 
	  exit(-1); 
	 } 
	 
	 return scon;
}

/* Envia a través del socket TCP “connectat” d’identificador “Sck” la     */
/* seqüència de bytes escrita a “SeqBytes” (de longitud “LongSeqBytes”    */
/* bytes) cap al socket TCP remot amb qui està connectat.                 */
/* "SeqBytes" és un vector de chars qualsevol (recordeu que en C, un      */
/* char és un enter de 8 bits) d'una longitud >= LongSeqBytes bytes.      */
/* Retorna -1 si hi ha error; el nombre de bytes enviats si tot va bé.    */
int TCP_Envia(int Sck, const char *SeqBytes, int LongSeqBytes)
{
	int bytes_escrits;
	if((bytes_escrits=write(Sck,SeqBytes,LongSeqBytes))==-1) 
	 { 
		  perror("Error en write"); 
		  close(Sck); 
		  exit(-1); 
	 } 
	 return bytes_escrits;
}

/* Rep a través del socket TCP “connectat” d’identificador “Sck” una      */
/* seqüència de bytes que prové del socket remot amb qui està connectat,  */
/* i l’escriu a “SeqBytes*” (que té una longitud de “LongSeqBytes” bytes),*/
/* o bé detecta que la connexió amb el socket remot ha estat tancada.     */
/* "SeqBytes*" és un vector de chars qualsevol (recordeu que en C, un     */
/* char és un enter de 8 bits) d'una longitud <= LongSeqBytes bytes.      */
/* Retorna -1 si hi ha error; 0 si la connexió està tancada; el nombre de */
/* bytes rebuts si tot va bé.                                             */
int TCP_Rep(int Sck, char *SeqBytes, int LongSeqBytes)
{
	int bytes_llegits;
	if(bytes_llegits=read(Sck,SeqBytes,LongSeqBytes)==-1) 
	 { 
		  perror("Error en read"); 
		  close(Sck); 
		  exit(-1); 
	 } 
	 return 0;
}

/* S’allibera (s’esborra) el socket TCP d’identificador “Sck”; si “Sck”   */
/* està connectat es tanca la connexió TCP que té establerta.             */
/* Retorna -1 si hi ha error; un valor positiu qualsevol si tot va bé.    */
int TCP_TancaSock(int Sck)
{
	return close(Sck); 
}

/* Donat el socket TCP d’identificador “Sck”, troba l’adreça d’aquest     */
/* socket, omplint “IPloc*” i “portTCPloc*” amb respectivament, la seva   */
/* @IP i #port TCP.                                                       */
/* "IPloc*" és un "string" de C (vector de chars imprimibles acabat en    */
/* '\0') d'una longitud màxima de 16 chars (incloent '\0').               */
/* Retorna -1 si hi ha error; un valor positiu qualsevol si tot va bé.    */
int TCP_TrobaAdrSockLoc(int Sck, char *IPloc, int *portTCPloc)
{
	
}

/* Donat el socket TCP “connectat” d’identificador “Sck”, troba l’adreça  */
/* del socket remot amb qui està connectat, omplint “IPrem*” i            */
/* “portTCPrem*” amb respectivament, la seva @IP i #port TCP.             */
/* "IPrem*" és un "string" de C (vector de chars imprimibles acabat en    */
/* '\0') d'una longitud màxima de 16 chars (incloent '\0').               */
/* Retorna -1 si hi ha error; un valor positiu qualsevol si tot va bé.    */
int TCP_TrobaAdrSockRem(int Sck, char *IPrem, int *portTCPrem)
{
	
}

/* Examina simultàniament i sense límit de temps (una espera indefinida)  */
/* els sockets (poden ser TCP, UDP i stdin) amb identificadors en la      */
/* llista “LlistaSck” (de longitud “LongLlistaSck” sockets) per saber si  */
/* hi ha arribat alguna cosa per ser llegida.                             */
/* "LlistaSck" és un vector d'enters d'una longitud >= LongLlistaSck      */
/* Retorna -1 si hi ha error; si arriba alguna cosa per algun dels        */
/* sockets, retorna l’identificador d’aquest socket.                      */
int T_HaArribatAlgunaCosa(const int *LlistaSck, int LongLlistaSck)
{
	
}

/* Obté un missatge de text que descriu l'error produït en la darrera     */
/* crida de sockets.                                                      */
/* Retorna aquest missatge de text en un "string" de C (vector de chars   */
/* imprimibles acabat en '\0')                                            */
char* T_MostraError(void)
{
 return strerror(errno);
} 

/* Si ho creieu convenient, feu altres funcions EXTERNES                  */

/* Definicio de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer.                                  */

