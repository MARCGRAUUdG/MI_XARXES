/**************************************************************************/
/*                                                                        */
/* P1 - MI amb sockets TCP/IP - Part I                                    */
/* Fitxer capçalera de mi.c                                               */
/*                                                                        */
/* Autors: X, Y                                                           */
/*                                                                        */
/**************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
/* Declaració de funcions EXTERNES de mi.c, és a dir, d'aquelles que es   */
/* faran servir en un altre fitxer extern, p.e., MIp1-p2p.c; el fitxer    */
/* extern farà un #include del fitxer .h a l'inici, i així les funcions   */
/* seran conegudes en ell.                                                */
/* En termes de capes de l'aplicació, aquest conjunt de funcions EXTERNES */
/* formen la interfície de la capa MI.                                    */
int MI_IniciaEscPetiRemConv(int portTCPloc);
int MI_HaArribatPetiConv(int SckEscMI);
int MI_DemanaConv(const char *IPrem, int portTCPrem, char *IPloc, int *portTCPloc, const char *NicLoc, char *NicRem);
int MI_AcceptaConv(int SckEscMI, char *IPrem, int *portTCPrem, char *IPloc, int *portTCPloc, const char *NicLoc, char *NicRem);
int MI_HaArribatLinia(int SckConvMI);
int MI_EnviaLinia(int SckConvMI, const char *Linia);
int MI_RepLinia(int SckConvMI, char *Linia);
int MI_AcabaConv(int SckConvMI);
int MI_AcabaEscPetiRemConv(int SckEscMI);
