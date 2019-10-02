/**************************************************************************/
/*                                                                        */
/* P1 - MI amb sockets TCP/IP - Part I                                    */
/* Fitxer capçalera de t.c                                                */
/*                                                                        */
/* Autors: X, Y                                                           */
/*                                                                        */
/**************************************************************************/

/* Declaració de funcions EXTERNES de t.c, és a dir, d'aquelles que es    */
/* faran servir en un altre fitxer extern, p.e., MIp1-mi.c; el fitxer     */
/* extern farà un #include del fitxer .h a l'inici, i així les funcions   */
/* seran conegudes en ell.                                                */
/* En termes de capes de l'aplicació, aquest conjunt de funcions EXTERNES */
/* són la "nova" interfície de la capa de transport (la "nova" interfície */
/* de sockets).                                                           */
int TCP_CreaSockClient(const char *IPloc, int portTCPloc);
int TCP_CreaSockServidor(const char *IPloc, int portTCPloc);
int TCP_DemanaConnexio(int Sck, const char *IPrem, int portTCPrem);
int TCP_AcceptaConnexio(int Sck, char *IPrem, int *portTCPrem);
int TCP_Envia(int Sck, const char *SeqBytes, int LongSeqBytes);
int TCP_Rep(int Sck, char *SeqBytes, int LongSeqBytes);
int TCP_TancaSock(int Sck);
int TCP_TrobaAdrSockLoc(int Sck, char *IPloc, int *portTCPloc);
int TCP_TrobaAdrSockRem(int Sck, char *IPrem, int *portTCPrem);
int T_HaArribatAlgunaCosa(const int *LlistaSck, int LongLlistaSck);
char* T_MostraError(void);