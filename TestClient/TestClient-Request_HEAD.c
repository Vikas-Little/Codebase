// A client program to request the server to return header information about a file which is present in the web_root directory
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUF_SIZE 1000

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUF_SIZE];
    int i = 0;
    char head_request[2000], str1[150], str2[150], str4[150];
    strncpy(str1, "", sizeof(str1));
    strncpy(str2, "", sizeof(str2));
    strncpy(str4, "", sizeof(str4));
    strncpy(head_request, "", sizeof(head_request));

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s hostname port\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket...");
    }

    portno = atoi(argv[2]);

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host.\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting...");
    }

    printf("Welcome!, You are now connected to LightHTTPServer.\n");
    printf("Please enter the name of the file to receive its header information:\n");
    scanf("%s", str2);
    printf("\n");
    sprintf(str1, "HEAD /%s HTTP/1.1\r\n", str2);
    char str3[] = "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36\r\n";
    sprintf(str4, "Host: %s\r\n", argv[1]);
    char str5[] = "Accept-Language: en-GB,en-US;q=0.8,en;q=0.6\r\n"
                  "Accept-Encoding: gzip, deflate, sdch, br\r\n"
                  "Connection: keep-alive\r\n\r\n";

    strcat(head_request, str1);
    strcat(head_request, str3);
    strcat(head_request, str4);
    strcat(head_request, str5);

    // printf("%s", head_request);

    n = write(sockfd, head_request, strlen(head_request));
    if (n < 0)
    {
        error("ERROR writing to socket...");
    }

    memset(buffer, 0, BUF_SIZE);

    n = read(sockfd, buffer, BUF_SIZE);
    if (n < 0)
    {
        error("ERROR reading from socket...");
    }

    printf("%s\n", buffer);
    close(sockfd);
    return 0;
}