#include <sys/types.h>
#include <sys/socket.h>
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
#if defined (WIN32)
	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);
#else
	int erreur = 0;
#endif


	// Création des deux sockets
	SOCKET sock;
	SOCKADDR_IN sin;
	SOCKET csock;
	SOCKADDR_IN csin;
	char buffer[32] = "salt je marche";
	char bufferClient[50] = { 0 };
	socklen_t recsize = sizeof(csin);
	int sockBind_err;
	int sockSend_err;
	int sockRecv_err;
	int PORT = 9015;

	if (!erreur)
	{
		
		sock = socket(AF_INET, SOCK_STREAM, 0);
		
		if (sock != INVALID_SOCKET)
		{

			printf("La socket %d ouverte \n", sock);

			sin.sin_addr.s_addr = htonl(INADDR_ANY);
			sin.sin_family = AF_INET;
			sin.sin_port = htons(PORT);
			
			sockBind_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
			
			if (sockBind_err != SOCKET_ERROR)
			{
				printf("en attente \n", PORT);
				listen(sock, 6);
				csock = accept(sock, (SOCKADDR*)&csin, &recsize);
				printf("Connecter\n");
				
				sockRecv_err = recv(csock, &bufferClient, sizeof(bufferClient), 0);
				
				if (sockRecv_err == -1)
				{
					printf("erreur");
				}
				else
				{
					
					printf(" reçu : %s\n", bufferClient);
				}
				
				sockSend_err = send(csock, buffer, 32, 0);

				if (sockSend_err != SOCKET_ERROR)
				{
					printf("Chaine envoyée : %s\n", buffer);
				}
				else
				{
					printf("Erreur de transmission\n");

					shutdown(csock, 2);
				}
			}
			else
			{
				printf("Pas reussi à bind le server");
			}

			printf("Fermeture de la socket...\n");
			close(sock);
			printf("Fermeture du serveur terminee\n");
		}
		else
		{
			printf("Pas reussi à creer la socket");
		}

#if defined (WIN32)
		WSACleanup();
#endif
	}
}