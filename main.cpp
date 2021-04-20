#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib"); //To link the winsock library 


int main(int argc, char **argv)
{

    WSADATA wsaData;
    SOCKET S;
    struct hostent *host;
    int err, i, startport, endport;
    struct sockaddr_in sa; //storing destination address
    char hostname[100];

    strncpy((char *)&sa, "", sizeof sa);
    sa.sin_family = AF_INET; 


    // Initialize Winsock version 2.2

    if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)

    {

        fprintf(stderr, "WSAStartup() failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter hostname or ip to scan: ");
    gets(hostname);

    printf("Enter starting port: ");
    scanf("%d", &startport);

    printf("Enter ending port: ");
    scanf("%d", &endtport);    

    

}