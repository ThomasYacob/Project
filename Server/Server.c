#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL2/SDL_net.h"

int main(int argc, char **argv)
{
	UDPsocket sd;
	UDPpacket *pReceive;
	UDPpacket *pSent;
	Uint32 IPclient1 = 0;
	Uint32 IPclient2 = 0;
	Uint32 portClient1 = 0;
	Uint32 portClient2 = 0;
	int a, b, c, quit;
	int counter = 0;

	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_UDP_Open(2000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!((pSent = SDLNet_AllocPacket(512)) && (pReceive = SDLNet_AllocPacket(512))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	quit = 0;
	while (!quit)
	{

		if (SDLNet_UDP_Recv(sd, pReceive))
		{
			if (IPclient1 == 0 && portClient1 == 0)
			{
				printf("Client 1 connected\n");
				IPclient1 = pReceive->address.host;
				portClient1 = pReceive->address.port;
				counter++;
				printf("Send to Client 1\n");
				pSent->address.host = IPclient1;
				pSent->address.port = portClient1;
				a = 1;
				printf("Sent Position For Client 1\n");
				sprintf((char *)pSent->data, "%d\n", a);
				pSent->len = strlen((char *)pSent->data) + 1;
				SDLNet_UDP_Send(sd, -1, pSent);
			}
			else if (pReceive->address.port != portClient1 && IPclient2 == 0)
			{
				printf("Client 2 connected\n");
				IPclient2 = pReceive->address.host;
				portClient2 = pReceive->address.port;
				counter++;
				a = 2;
				printf("Send to Client 2\n");
				pSent->address.host = IPclient2;
				pSent->address.port = portClient2;
				printf("Sent Position For Client 2\n");
				sprintf((char *)pSent->data, "%d\n", a);
				pSent->len = strlen((char *)pSent->data) + 1;
				SDLNet_UDP_Send(sd, -1, pSent);
			}
			else
			{
				if (pReceive->address.port == portClient1)
				{
					printf("Received data from client 1\n");
					if (IPclient2 != 0)
					{
						printf("Send to Client 2\n");
						pSent->address.host = IPclient2;
						pSent->address.port = portClient2;
						sscanf((char *)pReceive->data, "%d %d %d\n", &a, &b, &c);
						printf("%d %d %d\n", a, b, c);
						sprintf((char *)pSent->data, "%d %d %d\n", a, b, c);
						pSent->len = strlen((char *)pSent->data) + 1;
						SDLNet_UDP_Send(sd, -1, pSent);
					}
				}
				else if (pReceive->address.port == portClient2)
				{
					printf("Received data from client 2\n");
					printf("Send to Client 1\n");
					pSent->address.host = IPclient1;
					pSent->address.port = portClient1;
					sscanf((char *)pReceive->data, "%d %d %d\n", &a, &b, &c);
					printf("%d %d %d\n", a, b, c);
					sprintf((char *)pSent->data, "%d %d %d\n", a, b, c);
					pSent->len = strlen((char *)pSent->data) + 1;
					SDLNet_UDP_Send(sd, -1, pSent);
				}
			}
			if (counter == 2)
			{
				a = 50;
				pSent->address.host = IPclient1;
				pSent->address.port = portClient1;
				printf("Sending Start to client 1\n");
				sprintf((char *)pSent->data, "%d\n", a);
				pSent->len = strlen((char *)pSent->data) + 1;
				SDLNet_UDP_Send(sd, -1, pSent);

				pSent->address.host = IPclient2;
				pSent->address.port = portClient2;
				printf("Sending start to client 2\n");
				sprintf((char *)pSent->data, "%d\n", a);
				pSent->len = strlen((char *)pSent->data) + 1;
				SDLNet_UDP_Send(sd, -1, pSent);
				printf("Sent start to both clients\n");
				counter = 0;
			}

			if (strcmp((char *)pSent->data, "quit") == 0)
				quit = 1;
		}
	}

	SDLNet_FreePacket(pSent);
	SDLNet_FreePacket(pReceive);
	SDLNet_Quit();
	return EXIT_SUCCESS;
}
