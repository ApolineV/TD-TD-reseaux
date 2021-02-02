//clément
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main()
{
SOCKET sock;
sock = socket(AF_INET, SOCK_DGRAM, 0);
fprintf(stderr, "socket() message: %s\n", strerror(errno));

SOCKADDR_IN destAddrUdp;
 destAddrUdp.sin_addr.s_addr = inet_addr("192.168.64.54");
 destAddrUdp.sin_family = AF_INET;
 destAddrUdp.sin_port = htons(9010);

char buffer[25];
 buffer[0]= 'c';
 buffer[1]= 'o';
 buffer[2]= 'u';
 buffer[3]= 'c';
 buffer[4]= 'o';
 buffer[5]= 'u';
 buffer[6]= ' ';
 buffer[7]= 'j';
 buffer[8]= 'e';
 buffer[9]= ' ';
 buffer[10]= 's';
 buffer[11]= 'u';
 buffer[12]= 'i';
 buffer[13]= 's';
 buffer[14]= ' ';
 buffer[15]= 'u';
 buffer[16]= 'n';
 buffer[17]= ' ';
 buffer[18]= 'c';
 buffer[19]= 'l';
 buffer[20]= 'i';
 buffer[21]= 'e';
 buffer[22]= 'n';
 buffer[23]= 't';
 buffer[24]= '\0';

 socklen_t tailleudp = sizeof(destAddrUdp);
 int error_message;
 error_message = sendto(sock,buffer,sizeof(buffer),0,
(SOCKADDR*)&destAddrUdp,sizeof(destAddrUdp));
 if(error_message == 0){
 fprintf(stderr, "sendto message erreur : %s\n", strerror(errno));
 }

close(sock);

}
