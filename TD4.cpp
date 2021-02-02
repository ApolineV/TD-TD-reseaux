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
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	fprintf(stderr, "socket() message: %s\n", strerror(errno));
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr("192.168.65.56");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9002);
	connect(sock, (SOCKADDR*)&sin, sizeof(sin));

	char buffer[8];
	buffer[0] = 'c';
	buffer[1] = 'c';
	buffer[2] = 'c';
	buffer[3] = 'a';
	buffer[4] = 'p';
	buffer[5] = 'o';
	buffer[6] = 'p';
	buffer[7] = 'o';

	int error_message;
	error_message = send(sock, buffer, sizeof(buffer), 0);
	if (error_message == 0) {
		fprintf(stderr, "sendto message erreur : %s\n", strerror(errno));
	}

	close(sock);

}