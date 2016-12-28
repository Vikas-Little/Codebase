#include "Parse.h"

void parse_field_data(struct WebRequest *web_request, struct WebForm *formData, char field_name[], char field_value[])
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

	int idx = field_index, tdx = 0;

	while (query_string[idx] != '=')
		{
			field_name[tdx++] = query_string[idx];
			idx++;
		}

	idx++, tdx = 0;

	while (query_string[idx] != '&' && idx < strlen(query_string))
		{
			field_value[tdx++] = query_string[idx];
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

	field_index = parse_form_field(web_request->query_string, field_name, field_value, 0); // parsing the form fields.
	
	while (field_index != -1)
	{
		parse_field_data(web_request, formData, field_name, field_value); // parsing the form field data.
		
		strncpy (field_name, "", sizeof (field_name));
		strncpy (field_value, "", sizeof (field_value));
		
		field_index = parse_form_field(web_request->query_string, field_name, field_value, field_index); // parsing the form fields.
	}
}

void parse_request_line (char *request_line, struct WebRequest *web_request, struct WebForm *formData)
{
	int line_index = 0, temp_index = 0, idx = 0, tdx = 0;
	char field_name[50], field_value[1000];
	strncpy (field_name, "", sizeof (field_name));
	strncpy (field_value, "", sizeof (field_value));						
		
	// Read till you read the first space
	while (request_line[line_index] != ' ')
	{
		field_name[temp_index++] = request_line[line_index++];
	}
	line_index++;
	
	// Read till you read the end of line data
	temp_index = 0;
	while (request_line[line_index] != '\r')
	{
		field_value[temp_index++] = request_line[line_index++];
	}
	
	 //printf ("FIELD NAME: %s, FIELD VALUE: %s\r\n", field_name, field_value);

	// Start identifying and storing the requests
	if (strcmp (field_name, "GET") == 0 || strcmp (field_name, "POST") == 0)
	{
		// Store 'http_method' header
		sprintf (web_request->http_method, "%s", field_name); 

		// Parse 'file' and 'protocol' headers
		temp_index = 1;
		
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
		
		// Checking whether the content in web_request->file contains the query string or not!
		const char needle = '?';
		char *ret;

 		// Look for the presence of '?'
		ret = strchr (web_request->file, needle);

		// If query string is present in web_request->file, then segregate the file name & the query string.
		if (ret > 0)
		{
			
			// Parse the 'file' header
			idx = 0; tdx = 0;
			while (web_request->file[idx] != '?')
			{
				web_request->req_file[tdx++] = web_request->file[idx];
				idx++;
			}
			
			idx++, tdx = 0;

			while (idx < strlen(web_request->file))
			{
				web_request->query_string[tdx++] = web_request->file[idx];
				idx++;
			}

			idx++, tdx = 0;

			parse_query_string (web_request, formData); // Parse the segregated query string.

		}
		else
		{			
			strcpy (web_request->req_file, web_request->file);
		}
	
		/*printf ("FILE: %s, PROTOCOL: %s\r\n", web_request->file, web_request->protocol);

		*/
		
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
	char request_line[1000];

	// Initialize WebForm structure elements
	strncpy (formData->first_name, "", sizeof (formData->first_name));
	strncpy (formData->last_name, "", sizeof (formData->last_name));
	strncpy (formData->age, "", sizeof (formData->age));
	strncpy (formData->email, "", sizeof (formData->email));
	strncpy (formData->address, "", sizeof (formData->address));

	// Initialize WebRequest structure elements
	strncpy (request_line, "", sizeof (request_line));
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
	
	// printf("request buffer is: %s", request_buffer);
	while (content_index < content_length)
	{
		// Read till you reach end of line, keep carriage return '\r' but ignore new line '\n'
		while (request_buffer[content_index] != '\n' && content_index < content_length)
		{
			request_line[line_index++] = request_buffer[content_index++];
		}
		/* For handling the POST request line!*/
		if(strstr(request_line, "\r") == NULL && strstr(request_line, " ") == NULL)
		{
				char new_request_line[1000];
				strcpy(new_request_line, "POST");
				strcat(new_request_line, " /");
				strcat(new_request_line, web_request->req_file);
				strcat(new_request_line, "?");
				strcat(new_request_line, request_line);
				strcat(new_request_line, " ");
				strcat(new_request_line, web_request->protocol);
				strcat(new_request_line, "\r");
				strcpy(request_line, new_request_line);
		}
		// printf("Request Line is: %s\r\n", request_line);
		// Ignore the line '\r\n'
		if (strlen (request_line) > 2)
		{
			// printf ("REQUEST LINE: %s\r\n", request_line);
			parse_request_line (request_line, web_request, formData);
		}

		// Re-initialize to empty string and reset line index	
		strncpy (request_line, "", sizeof (request_line));
		line_index = 0;

		// Move to the next character
		content_index++;
	}
}

void print_request (struct WebRequest *web_request, struct WebForm *formData)
{
	printf ("PRINTING RECEIVED WEB REQUEST:\r\n");
    printf ("Host: 			%s\r\n", web_request->host);
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
	printf ("Pragma: 		%s\r\n", web_request->pragma);

	printf("\nPRINTING QUERY STRING PARAMETERS:\n");
	printf("First Name:		%s\r\n", formData->first_name);
	printf("Last Name:		%s\r\n", formData->last_name);
	printf("Age:			%s\r\n", formData->age);
	printf("Email:			%s\r\n", formData->email);
	printf("Address:		%s\r\n", formData->address);
}