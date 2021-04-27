#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib") //To link the winsock library 


int main(int argc, char **argv)
{

    WSADATA wsaData;
    SOCKET s;
    struct hostent *host;
    int err, i, startport, endport, errCode, msg;
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
    scanf("%d", &endport);    

    if (isdigit(hostname[0]))
    {
        printf("Doing inet_addr...");
        sa.sin_addr.s_addr = inet_addr(hostname);
        printf("Done\n");
    }
    else if ((host = gethostbyname(hostname)) != 0)
    {
        printf("Doing gethostbyname()...");
        strncpy((char*)&sa.sin_addr, (char*)host->h_addr_list[0], sizeof sa.sin_addr);
        printf("Done\n");
    }
    else
    {
        printf("Error resolving hostname");
        exit(EXIT_FAILURE);
    }

    //Start the portscan loop
    printf("Starting the scan loop...\n");
    for (i = startport; i <= endport; i++)
    {

        s = socket(AF_INET, SOCK_STREAM, 0); //make net a valid socket handle
        if (s < 0)  //if not a socket
        {
            perror("\nSocket creation failed");  // perror function prints an error message to stderr
            exit(EXIT_FAILURE);       //or exit(0);
        }

        sa.sin_port = htons(i);
        //connect to the server with that socket
        err = connect(s, (struct sockaddr*)&sa, sizeof sa);

        //error handling
        errCode = WSAGetLastError();
        LPSTR errString = 0;
        DWORD msg = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM, 0, errCode, 0, (LPSTR)&errString, 0, 0);
                       
        if (err == SOCKET_ERROR) //connection not accepted, throw error code
        {
            printf("%s %-5d Winsock Error Code : %d\n", hostname, i, msg);
            fflush(stdout);
                                
        }
        else  //connection accepted
        {
            printf("%s %-5d accepted            \n", hostname, i);
            if (shutdown(s, SD_BOTH) == SOCKET_ERROR)
            {
                perror("\nshutdown");// perror function prints an error message to stderr
                exit(EXIT_FAILURE);
            }
        }
        
        closesocket(s);   //closes the net socket 
    }

    fflush(stdout); //clears the contents of a buffer or flushes a stream
    return(0);

}