// A client program to request the server to store the included entity-body at a location specified by the given URL
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUF_SIZE 2000

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
    char PUT_REQUEST[] =                    "PUT /Sample.htm HTTP/1.1\r\n"
                                            "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36\r\n"
                                            "Host: 127.0.0.1:4444\r\n"
                                            "Accept-Language: en-GB,en-US;q=0.8,en;q=0.6\r\n"
                                            "Connection: keep-alive\r\n"
                                            "Content-type: text/html\r\n"
                                            "Content-Length: 182\r\n"
                                            "<html>\r\n"
                                            "<body>\r\n"
                                            "<h1>201 Created</h1>\r\n"
                                            "</body>\r\n"
                                            "</html>\r\n";
    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
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
        fprintf(stderr,"ERROR, no such host.\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting...");
    }
    
    n = write(sockfd,PUT_REQUEST,strlen(PUT_REQUEST));
    if (n < 0)
    {
        error("ERROR writing to socket...");
    }
    
    memset(buffer, 0, BUF_SIZE);
    n = read(sockfd,buffer,BUF_SIZE);
    if (n < 0)
    {
        error("ERROR reading from socket...");
    }

    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}