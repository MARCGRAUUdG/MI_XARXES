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
 int sesc, scon, i; 
 int bytes_llegits, bytes_escrits; 
 char buffer[200]; 
 int long_adrrem;
 struct sockaddr_in adrloc, adrrem; 
 char iploc[16]; 
 int portloc; 
 int s2=0;
 /* Es crea el socket TCP sesc del servidor (el socket "local"), que de moment no té     */ 
 /* adreça (@IP i #port TCP) assignada.                                                  */ 
 TCP_CreaSockServidor("23.3.1.5,TCP,3678");
 TCP_AcceptaConnexio(s2,"88.8.12.3,TCP,2000");
 TCP_Rep(s2,"Com va això?");
 TCP_Rep(s2,"Estàs bé?");
 TCP_TancaSock(s2);
 
if((sesc=socket(AF_INET,SOCK_STREAM,0))==-1)
 { 
  perror("Error en socket"); 
  exit(-1); 
 } 
 /* Per assignar adreça a sesc (@IP i #port TCP) el programador ho pot fer de 2 maneres: */ 
 /* i) explícitament, és a dir, assignant uns valors concrets en el codi, fent bind()    */ 
 /* amb aquests valors; ii) implícitament, és a dir, deixant que els assigni el S.O.,    */ 
 /* que escull una @IP qualsevol de la màquina i un #port TCP que estigui lliure. Una    */ 
 /* assignació implicita es pot fer d'1 manera: fent bind() amb @IP 0.0.0.0 (que vol dir */ 
 /* qualsevol, és a dir, totes les @IP de la màquina) i #port TCP 0 (llavors, després    */ 
 /* del bind(), el S.O. haurà assignat un #port TCP, i després del accept() el S.O.      */ 
 /* haurà assignat una @IP, la 
de la interfície d'entrada). Assignar l'@IP 0.0.0.0 vol   */ 
 /* dir que el socket queda lligat a totes les @IP de la màquina i que escoltarà         */ 
 /* peticions de connexió que arribin a qualsevol d'elles.                               */ 
 /* Aquí es fa bind amb @IP 0.0.0.0 i #port TCP 3000.                                    */ 
 strcpy(iploc,"0.0.0.0");    /* 0.0.0.0 correspon a INADDR_ANY */ 
 portloc = 3000; 
 adrloc.sin_family=AF_INET; 
 adrloc.sin_port=htons(portloc); 
 adrloc.sin_addr.s_addr=inet_addr(iploc);    /* o bé: ...s_addr = INADDR_ANY */ 
 for(i=0;i<8;i++){adrloc.sin_zero[i]='\0';} 
 if((bind(sesc,(struct sockaddr*)&adrloc,sizeof(adrloc)))==-1) 
 { 
  perror("Error en bind"); 
  close(sesc); 
  exit(-1); 
 } 
/* Es crea una cua per emmagatzemar peticions de connexió pendents. 
                     */ 
 if((listen(sesc,3))==-1) 
 { 
  perror("Error en listen"); 
  close(sesc); 
  exit(-1); 
 } 
 /* Un cop fet listen() es diu que sesc és un socket "d'escolta".
                        */ 
 /* Ara espera una 
petició de connexió TCP d’un client, i un cop rebuda, l'accepta. El   */ 
 /* descriptor de socket retornat, scon, serà un nou identificador del socket local per  */ 
 /* a la connexió que s'acaba d'establir. Ambdós sockets tenen la mateixa adreça (@IP i  */
 /* #port TCP), però sesc és un socket “d’escolta” i scon és un socket "connectat". En   */ 
 /* aquest cas, però, com que sesc no tenia assignada una @IP concreta, sinó qualsevol,  */ 
 /* és a dir, totes les de la màquina (l'@IP 0.0.0.0), scon tindrà la “mateixa” @IP,     */ 
 /* però “concretada” a una d’elles (el S.O. li assignarà l’@IP que hagi fet servir el   */ 
 /* client en la petició de connexió).                                                   */ 
 long_adrrem=sizeof(adrrem); 
 if((scon=accept(sesc,(struct sockaddr*)&adrrem, &long_adrrem))==-1) 
 { 
  perror("Error en accept"); 
  close(sesc); 
  exit(-1); 
 } 
 /* Ara 
adrrem conté l'adreça del socket remot (@IP i #port TCP).                        */ 
 /* S'escriu a pantalla el que arriba pel socket connectat scon                          */ 
 if((bytes_llegits=read(scon,buffer,sizeof(buffer)))==-1) 
 { 
  perror("Error en read"); 
  close(scon); 
  exit(-1); 
 } 
 if((bytes_escrits=write(1,buffer,bytes_llegits))==-1) 
 { 
  perror("Error en write"); 
  close(scon); 
  exit(-1); 
 } 
 /* Es tanca el socket scon, que com que és un socket TCP, també vol dir que es tanca la */  
  /* connexió TCP establerta, i es tanca el socket d'escolta sesc.                        */ 
 close(scon); 
 close(sesc); 
 return(0); 
} 
