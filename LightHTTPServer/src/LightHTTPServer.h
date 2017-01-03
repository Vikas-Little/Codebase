#ifndef _LIGHTHTTPSERVER_H
#define _LIGHTHTTPSERVER_H

#include "config.h"
#include "WebPage.h"
#include "FileUtility.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>


int sockfd, newsockfd;
struct sockaddr_in cl_addr, addr;
char clientAddr[CLADDR_LEN];
char buffer[BUF_SIZE];
char Files_Array[200][256];

struct WebRequest
{
	char http_method[5];
	char query_string[1000];
	char file[1000];
	char req_file[1000];
    char protocol[10];
	char host[20];
	char connection_type[15];
	char accept_media[200];
	char referer[100];
	char user_agent[200];
	char accept_encoding[100];
	char accept_language[50];
	char upgrade_insecure_requests[10];	
	char cache_control[50];
	char pragma[50];
};

struct WebForm
{
	char first_name[100];
	char last_name[100];
   	char age[5];
   	char email[100];
   	char address[500];
};

void start_server();

void accept_connection();

void receive_data();

void set_http_response(char req_file[]);

void send_data(int , char *);

void send_header();

void quitproc (int );

#endif