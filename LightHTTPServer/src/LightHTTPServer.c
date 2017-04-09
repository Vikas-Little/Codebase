// The Server Program
#include "LightHTTPServer.h"

int http_response = HTTP_RESPONSE_OK;

char default_200_ok_status_line[] = "HTTP/1.1 200 OK\r\n";
char put_201_created_status_line[] = "HTTP/1.1 201 Created\r\n";
char not_found_404_status_line[] = "HTTP/1.1 404 NOT FOUND\r\n";

char default_200_ok_res_hdr_bdy[] = "Content-Type: text/html\r\n"
									"Connection: close\r\n"
									"Max-Age: 0\r\n"
									"Expires: 0\r\n"
									"Cache-Control: no-cache, private\r\n"
									"Pragma: no-cache\r\n\r\n";

char head_200_ok_res_hdr_bdy[] =	"Content-Type: text/html\r\n"
									"Vary: Authorization,Accept\r\n"
									"Accept-Ranges: bytes\r\n"
									"Content-length: 1598\r\n"
									"Connection: close\r\n\r\n";

char delete_200_ok_res_hdr_bdy[] =	"Content-Type: text/html\r\n"
									"Connection: close\r\n"
									"Content-length: 30\r\n"
									"\r\n"
									"<html>\r\n"
									"<body>\r\n"
									"<h1>URL deleted.</h1>\r\n"
									"</body>\r\n"
									"</html>\r\n\r\n";

char put_201_created_res_hdr_bdy[] = 	"Content-Type: text/html\r\n"
										"Connection: close\r\n"
										"Content-length: 30\r\n"
										"\r\n"
										"<html>\r\n"
										"<body>\r\n"
										"<h1>The file was created/updated.</h1>\r\n"
										"</body>\r\n"
										"</html>\r\n\r\n";

char not_found_404_res_hdr_bdy[] = 	"Connection: close\r\n"
									"Max-Age: 0\r\n"
									"Expires: 0\r\n"
									"Cache-Control: no-cache, private\r\n"
									"Pragma: no-cache\r\n"
									"Content-Type: text/html\r\n\r\n";

char content_inline_res_hdr_bdy[] = "Connection: close\r\n"
									"Max-Age: 0\r\n"
									"Expires: 0\r\n"
									"Cache-Control: no-cache, private\r\n"
									"Pragma: no-cache\r\n"
									"Content-Type: application/pdf\r\n"
									"Content-Disposition: inline\r\n\r\n";

char response_header_content_css[] =	"HTTP/1.1 200 OK\r\n"
										"Server: LightHTTPServer/1.0\r\n"
										"Connection: close\r\n"
										"Max-Age: 0\r\n"
										"Expires: 0\r\n"
										"Cache-Control: no-cache, private\r\n"
										"Pragma: no-cache\r\n"
										"Content-Type: text/css\r\n\r\n";

char response_header_file_attachment[] =    "HTTP/1.1 200 OK\r\n"
                                            "Server: LightHTTPServer/1.0\r\n"
                                            "Connection: close\r\n"
                                            "Max-Age: 0\r\n"
                                            "Expires: 0\r\n"
                                            "Cache-Control: no-cache, private\r\n"
                                            "Pragma: no-cache\r\n"
                                            "Content-Type: application/download\r\n"  
                                            "Content-Disposition: attachment\r\n\r\n";

void start_server()
{
	int ret;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		printf("Error creating socket!\n");
		exit(1);
	}
	printf("Socket created...\n");
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	
	ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	if (ret < 0) 
	{
		perror("Error binding");
		exit(1);
	}
	printf("Binding done...\n");

	int option = 1;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (ret < 0) 
	{
		perror("setsockopt");
		exit(1);
	}
	printf("Socket options set...\n");

	printf("Waiting for a connection...\n");
	listen(sockfd, 5);
}

void accept_connection()
{
	int len = sizeof(cl_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);

    if (newsockfd < 0) 
    {
      printf("Error accepting connection!\n");
      exit(1);
    }
    printf("Connection accepted...\n");
	inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
}

void receive_data()
{
	memset(buffer, 0, BUF_SIZE);
	int len = sizeof(cl_addr);
	int ret = recvfrom(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);
	if(ret < 0) 
	{
		printf("Error receiving data!\n");  
		exit(1);
	}
	printf("Received data from %s: %s\n", clientAddr, buffer);
}

void set_http_response(struct WebRequest *web_request, char req_file[])
{
			char ch = '.';
			char *r = strchr(req_file, ch);

			if (strcmp (r, ".pdf") == 0)
			{
				http_response = HTTP_RESPONSE_CONTENT_INLINE;
			}
			
			else if (strcmp (r, ".html") == 0)
			{
				http_response = HTTP_RESPONSE_OK;
			}
			
			else if(strcmp (r, ".css") == 0)
			{
				http_response = HTTP_RESPONSE_FILE_CSS;
			}
			
			else
			{
				http_response = HTTP_RESPONSE_FILE_OTHER;
			}
}

void send_data(int length, char *content)
{
	int len = sizeof(cl_addr);
	int ret = sendto(newsockfd, content, length, MSG_OOB, (struct sockaddr *) &cl_addr, len);
	if (ret < 0) 
	{  
		printf("Error sending data: %d, %s\n", errno, strerror(errno));  
		exit(1);  
	}
}
 
void construct_response_header(char str1[], char str5[])
{
    display_current_time_date();
	char temp[100], str2[100], str4[100];
	strncpy(str2,"",sizeof(str2)); strncpy(temp,"",sizeof(temp)); strncpy(str4,"",sizeof(str4));
	strncpy(response_header,"",sizeof(response_header));
    sprintf(str2, "Date: %s", current_tm_dt);
    int content_index = 0, line_index = 0;
    while (str2[content_index] != '\n')
    {
        temp[line_index++] = str2[content_index++];
    }
    strcpy(str2, temp);
    strcat(str2, "\r\n");    
    char str3[] = "Server: LightHTTPServer/1.0\r\n";
    sprintf(str4, "Last-Modified: %s\r\n", file_mod_status);
    strcpy(response_header, str1);
    strcat(response_header, str2);
    strcat(response_header, str3);
    strcat(response_header, str4);
	/*sprintf(content_length, "Content-Length: %d\r\n", length);
	strcat(response_header, content_length);*/
	strcat(response_header, str5);
	printf("%s", response_header);
}

void send_header()
{
	if (http_response == HTTP_RESPONSE_NOT_FOUND)
	{
		construct_response_header(not_found_404_status_line, not_found_404_res_hdr_bdy);
		send_data (sizeof(response_header), response_header);
	}
	
	else if (http_response == HTTP_RESPONSE_OK)
	{
		construct_response_header(default_200_ok_status_line, default_200_ok_res_hdr_bdy);
		send_data (sizeof(response_header), response_header);
	}
	
	else if (http_response == HTTP_RESPONSE_CONTENT_INLINE)
	{
		construct_response_header(default_200_ok_status_line, content_inline_res_hdr_bdy);
		send_data (sizeof(response_header), response_header);
	}
	
	else if (http_response == HTTP_RESPONSE_FILE_OTHER)
	{
		send_data (sizeof(response_header_file_attachment), response_header_file_attachment);
	}
	
	else if (http_response == HTTP_RESPONSE_FILE_CSS)
	{
		send_data (sizeof(response_header_content_css), response_header_content_css);
	}

	else if (http_response == HTTP_RESPONSE_DELETE)
	{
		construct_response_header(default_200_ok_status_line, delete_200_ok_res_hdr_bdy);
		send_data (sizeof(response_header), response_header);
	}

	else if (http_response == HTTP_RESPONSE_PUT)
	{
		construct_response_header(put_201_created_status_line, put_201_created_res_hdr_bdy);
		send_data (sizeof(response_header), response_header);
	}

	else if (http_response == HTTP_RESPONSE_HEAD)
	{
		construct_response_header(default_200_ok_status_line, head_200_ok_res_hdr_bdy);
		send_data (sizeof(response_header), response_header);
	}
}

void quitproc (int sig_num)
{
  if (sig_num == SIGINT)
  {
    printf ("\rReceived Signal [Ctrl-C]. \n/-----------------------Terminating Program-------------------------------------/\r\n");
  }

  shutdown (sockfd, SHUT_RDWR);
  close (sockfd);

  shutdown (newsockfd, SHUT_RDWR);
  close (newsockfd);

  printf("\rClosed socket file descriptors\n");
  exit(0);
}

int main () 
{
  signal (SIGINT, quitproc);
  signal (SIGQUIT, quitproc);

  int ret;
  pid_t childpid;

  start_server();

  for (;;) // infinite loop
  { 
	accept_connection();

    if ((childpid = fork()) == 0) 
    { // creating a child process

      close (sockfd); // not needed in child process

      for (;;) 
      {
         receive_data();
	
		struct WebRequest new_request;
		struct WebForm formData;

		// parse the received web request
		parse_request (&new_request, buffer, &formData);
	
		// ignore this request for printing
		if (strcmp (new_request.req_file, "favicon.ico") != 0)
		{
			print_request (&new_request, &formData);
		}
		
		FILE *fp;
		char *content = 0;
		int length;
		char local_file_location[200];
		sprintf(local_file_location, "/home/vikash/Documents/Codebase/LightHTTPServer/web_root/%s", new_request.req_file);

		if (is_directory(local_file_location))
		{
			// check for the index file: index.html
			fp = check_dir_index_file(local_file_location);
			
			// if index.html is not present, then list the directory files
			if (fp == NULL)
			{
				 content = malloc(4000);
				 get_directory_files(local_file_location);
				 char main_content[200];
				 /*  int i = 0;
				 printf("Contents in Files_Array:\r\n");
				 for (i = 0; i < 10; i++)
				 {
					printf("%s\n", Files_Array[i]);
				 } */
				 strcpy(main_content, Files_Array);
				 struct WebLink links[4];		
				
				 strcpy (links[0].link_name, "Google");
				 strcpy (links[0].link_address, "http://www.google.com");
				 strcpy (links[1].link_name, "Planys");
				 strcpy (links[1].link_address, "http://www.planystech.com");
				 strcpy (links[2].link_name, "UPES");
				 strcpy (links[2].link_address, "http://www.upes.ac.in");
				 strcpy (links[3].link_name, "XYZ");
				 strcpy (links[3].link_address, "http://www.microsoft.com");

				get_web_page_content("Web Page Title", main_content, links, content);
				length = strlen(content);
				// printf("Web page is %lu bytes:\n%s\n", sizeof(web_page_content), content);
			}
		}

		// Load the file into memory and then send it		
		else
		{
			fp = get_requested_file_pointer(&new_request, new_request.req_file, local_file_location);
		}
		
		if (strcmp (new_request.http_method, "HEAD") != 0)
		{
			// read the entire content of the file pointed by fp
			if (fp != NULL && content == NULL)
			{
				length = get_file_size(fp);
				content = malloc(length);
				read_file(fp, content, length);
			}
		}
		
		// send data to the client
		send_header();
		//printf("length: %d, content: %s\r\n", length, content);
		send_data (length, content);

        break;
      }

      close (newsockfd);
      exit(0);
    }   

    close(newsockfd);
  }
  return 0;
}