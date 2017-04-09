#include "Parse.h"

void parse_form_field_data(struct WebRequest *web_request, struct WebForm *formData, char field_name[], char field_value[])
{
	if (strcmp (field_name, "fname") == 0)
	{
		sprintf (formData->first_name, "%s", field_value); 
	}

	else if (strcmp (field_name, "lname") == 0)
	{
		sprintf (formData->last_name, "%s", field_value); 
	}

	else if (strcmp (field_name, "age") == 0)
	{
		sprintf (formData->age, "%s", field_value); 
	}

	else if (strcmp (field_name, "email") == 0)
	{
		sprintf (formData->email, "%s", field_value); 
	}

	else if (strcmp (field_name, "addr") == 0)
	{
		sprintf (formData->address, "%s", field_value); 
	}
}

int parse_form_field (char *query_string, char *field_name, char *field_value, int field_index)
{
	if (field_index >= strlen (query_string)) 
	
	return -1;

	int idx = field_index, content_index = 0;

	while (query_string[idx] != '=')
		{
			field_name[content_index++] = query_string[idx];
			idx++;
		}

	idx++, content_index = 0;

	while (query_string[idx] != '&' && idx < strlen(query_string))
		{
			field_value[content_index++] = query_string[idx];
			idx++;
		}
	
	idx++;

	return idx;
}

void parse_query_string (struct WebRequest *web_request, struct WebForm *formData)
{
	int field_index;
	char field_name[50], field_value[1000];
	strncpy (field_name, "", sizeof (field_name));
	strncpy (field_value, "", sizeof (field_value));

	field_index = parse_form_field(web_request->query_string, field_name, field_value, 0); // Parse the form fields
	
	while (field_index != -1)
	{
		parse_form_field_data(web_request, formData, field_name, field_value); // Parse the form field data
		
		strncpy (field_name, "", sizeof (field_name));
		strncpy (field_value, "", sizeof (field_value));
		
		field_index = parse_form_field(web_request->query_string, field_name, field_value, field_index);
	}
}

void parse_request_line(struct WebRequest *web_request, char *field_name, char *field_value)
{
        // Store 'http_method' header
		sprintf (web_request->http_method, "%s", field_name); 

		// Parse 'file' and 'protocol' headers
		int temp_index = 1;
		int idx = 0;

		// Parse 'file' header
		while (field_value[temp_index] != ' ')
		{
			web_request->file[idx++] = field_value[temp_index];
			temp_index++;
		}

		// Parse 'protocol' header
		idx = 0;
		temp_index++;
		
		while (temp_index < strlen(field_value))
		{
			web_request->protocol[idx++] = field_value[temp_index];
			temp_index++;
		}
		
		strcpy (web_request->req_file, web_request->file);
		file_modification_status(web_request);
}

int create_req_file(struct WebRequest *web_request, char *request_message_line)
{
        int content_index = 0, line_index = 0; char temp_buffer[1000];
        strncpy (temp_buffer, "", sizeof (temp_buffer));
		int request_message_line_len = strlen(request_message_line);
		
		while (content_index < request_message_line_len)
		{
			temp_buffer[line_index++] = request_message_line[content_index++];
		}

        char PATH[50];
        sprintf(PATH, "/home/vikash/Documents/Codebase/LightHTTPServer/web_root/%s", web_request->req_file);
		//printf("PATH: %s\n", PATH);
        
		FILE *fp;
		
		fp = fopen(PATH, "a");
        
		if (fp == NULL)
        {
            printf("File does not exists!\n");
            return;
        }

        fprintf(fp, "%s", request_message_line);

        fclose(fp);
		return 201;
}

void parse_request_message_line (char *request_message_line, struct WebRequest *web_request, struct WebForm *formData)
{
	int line_index = 0, temp_index = 0, idx = 0, content_index = 0;
	char field_name[50], field_value[1000];
	
	strncpy (field_name, "", sizeof (field_name));
	strncpy (field_value, "", sizeof (field_value));						

	if (strcmp (web_request->http_method, "PUT") == 0 && strstr(request_message_line, "<") != NULL && strstr(request_message_line, ">") != NULL)
	{
		http_response = create_req_file(web_request, request_message_line);
	}
	
	else
	{
		// Read till you see the first space
		while (request_message_line[line_index] != ' ')
		{
			field_name[temp_index++] = request_message_line[line_index++];
		}
			line_index++;
		
		// Read till you come to the end of line data
		temp_index = 0;
		while (request_message_line[line_index] != '\r')
		{
			field_value[temp_index++] = request_message_line[line_index++];
		}
	}
	
	 //printf ("FIELD NAME: %s, FIELD VALUE: %s\r\n", field_name, field_value);

	// Start identifying and storing the requests
	if (strcmp (field_name, "GET") == 0 || strcmp (field_name, "POST") == 0 || strcmp (field_name, "HEAD") == 0)
	{
		
		parse_request_line(web_request, field_name, field_value);
			
		// Checking whether the content in web_request->file has the query string or not
		const char needle = '?';
		char *ret;

 		// Look for the presence of '?'
		ret = strchr (web_request->file, needle);

		// If the query string is present in web_request->file, then segregate the file name & the query string
		if (ret > 0)
		{
			// Parse the 'file' header
			idx = 0; content_index = 0;
			strncpy (web_request->req_file, "", sizeof (web_request->req_file));

			while (web_request->file[idx] != '?')
			{
				web_request->req_file[content_index++] = web_request->file[idx];
				idx++;
			}
			
			idx++, content_index = 0;

			while (idx < strlen(web_request->file))
			{
				web_request->query_string[content_index++] = web_request->file[idx];
				idx++;
			}

			idx++, content_index = 0;

			parse_query_string (web_request, formData); // Parse the segregated query string

		}

		else
		{			
			// do nothing
		}
	
		/*printf ("FILE: %s, PROTOCOL: %s\r\n", web_request->file, web_request->protocol);

		*/
	}

	else if (strcmp (field_name, "DELETE") == 0)
	{
		parse_request_line(web_request, field_name, field_value);
		
		// delete the requested file
		remove_status = delete_requested_file(web_request, web_request->req_file);
	}
	
	else if (strcmp (field_name, "PUT") == 0)
	{
        parse_request_line(web_request, field_name, field_value);

		// delete the previously existing file which has the same name as the requested file
		delete_prev_existing_file(web_request, web_request->req_file);
	}

	else if (strcmp (field_name, "Host:") == 0)
	{
		sprintf (web_request->host, "%s", field_value); 
	}

	else if (strcmp (field_name, "Connection:") == 0)
	{
		sprintf (web_request->connection_type, "%s", field_value); 
	}

	else if (strcmp (field_name, "Accept-Encoding:") == 0)
	{
		sprintf (web_request->accept_encoding, "%s", field_value); 
	}
    
	else if (strcmp (field_name, "Referer:") == 0)
	{
		sprintf (web_request->referer, "%s", field_value); 
	}
    
	else if (strcmp (field_name, "User-Agent:") == 0)
	{
		sprintf (web_request->user_agent, "%s", field_value); 
	}

    else if (strcmp (field_name, "Accept-Language:") == 0)
	{
		sprintf (web_request->accept_language, "%s", field_value); 
	}

    else if (strcmp (field_name, "Upgrade-Insecure-Requests:") == 0)
	{
		sprintf (web_request->upgrade_insecure_requests, "%s", field_value); 
	}

    else if (strcmp (field_name, "Cache-Control:") == 0)
	{
		sprintf (web_request->cache_control, "%s", field_value); 
	}

    else if (strcmp (field_name, "Pragma:") == 0)
	{
		sprintf (web_request->pragma, "%s", field_value); 
	}	
}

void parse_request (struct WebRequest *web_request, char *request_buffer, struct WebForm *formData)
{
	// A string to hold one line of data from the request buffer, initialize the string to be an empty string
	char request_message_line[1000];
	strncpy (request_message_line, "", sizeof (request_message_line));

	// Initialize the WebForm structure elements as an empty string
	strncpy (formData->first_name, "", sizeof (formData->first_name));
	strncpy (formData->last_name, "", sizeof (formData->last_name));
	strncpy (formData->age, "", sizeof (formData->age));
	strncpy (formData->email, "", sizeof (formData->email));
	strncpy (formData->address, "", sizeof (formData->address));

	// Initialize the WebRequest structure elements as an empty string
	strncpy (web_request->http_method, "", sizeof (web_request->http_method));
	strncpy (web_request->query_string, "", sizeof (web_request->query_string));
	strncpy (web_request->file, "", sizeof (web_request->file));
	strncpy (web_request->req_file, "", sizeof (web_request->req_file));
	strncpy (web_request->protocol, "", sizeof (web_request->protocol));
	strncpy (web_request->host, "", sizeof (web_request->host));
	strncpy (web_request->connection_type, "", sizeof (web_request->connection_type));
	strncpy (web_request->accept_media, "", sizeof (web_request->accept_media));
	strncpy (web_request->referer, "", sizeof (web_request->referer));
	strncpy (web_request->user_agent, "", sizeof (web_request->user_agent));
	strncpy (web_request->accept_encoding, "", sizeof (web_request->accept_encoding));
	strncpy (web_request->accept_language, "", sizeof (web_request->accept_language));
	strncpy (web_request->upgrade_insecure_requests, "", sizeof (web_request->upgrade_insecure_requests));
	strncpy (web_request->cache_control, "", sizeof (web_request->cache_control));
	strncpy (web_request->pragma, "", sizeof (web_request->pragma));

	long content_length = strlen (request_buffer);
	int content_index = 0, line_index = 0;
	
	//printf("REQUEST BUFFER: %s", request_buffer);
	while (content_index < content_length)
	{
		// Read till you reach end of line, keep carriage return '\r' but ignore new line '\n'
		while (request_buffer[content_index] != '\n' && content_index < content_length)
		{
			request_message_line[line_index++] = request_buffer[content_index++];
		}

		// Handle the POST request line
		if(strstr(request_message_line, "\r") == NULL && strstr(request_message_line, " ") == NULL)
		{
				char temp_var[1000];
				strcpy(temp_var, "POST");
				strcat(temp_var, " /");
				strcat(temp_var, web_request->req_file);
				strcat(temp_var, "?");
				strcat(temp_var, request_message_line);
				strcat(temp_var, " ");
				strcat(temp_var, web_request->protocol);
				strcat(temp_var, "\r");
				strcpy(request_message_line, temp_var);
		}
		
		// printf("REQUEST MESSAGE LINE: %s\r\n", request_message_line);
		// Ignore the line '\r\n'
		if (strlen (request_message_line) > 2)
		{
			// printf ("REQUEST MESSAGE LINE: %s\r\n", request_message_line);
			parse_request_message_line (request_message_line, web_request, formData);
		}

		// Re-initialize to empty string and reset line index	
		strncpy (request_message_line, "", sizeof (request_message_line));
		line_index = 0;

		// Move to the next character
		content_index++;
	}

}

void print_request (struct WebRequest *web_request, struct WebForm *formData)
{
	printf ("PRINTING RECEIVED WEB REQUEST:\r\n");
    printf ("Host: 		        %s\r\n", web_request->host);
	printf ("HTTP Method: 		%s\r\n", web_request->http_method);
	printf ("Request File: 		%s\r\n", web_request->req_file);
	printf ("Request Protocol: 	%s\r\n", web_request->protocol);
	printf ("Connection: 		%s\r\n", web_request->connection_type);
	printf ("Accept-Encoding: 	%s\r\n", web_request->accept_encoding);
	printf ("Referer: 		%s\r\n", web_request->referer);
	printf ("User-Agent: 		%s\r\n", web_request->user_agent);
	printf ("Accept-Language: 	%s\r\n", web_request->accept_language);
	printf ("Upgrade-Insecure-Requests: %s\r\n", web_request->upgrade_insecure_requests);
	printf ("Cache-Control: 	%s\r\n", web_request->cache_control);
	printf ("Pragma: 			%s\r\n", web_request->pragma);

	printf("\nPRINTING QUERY STRING PARAMETERS:\n");
	printf("First Name:		%s\r\n", formData->first_name);
	printf("Last Name:		%s\r\n", formData->last_name);
	printf("Age:			%s\r\n", formData->age);
	printf("Email:			%s\r\n", formData->email);
	printf("Address:		%s\r\n", formData->address);
}