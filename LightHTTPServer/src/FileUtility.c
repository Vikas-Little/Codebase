#include "FileUtility.h"

void read_file (FILE *fp, char content[], long length)
{
	// Read the entire file content of the file pointed by fp
	fseek (fp, 0, SEEK_SET);
	fread (content, 1, length, fp);
	fclose(fp);
}

long get_file_size(FILE *fp)
{
	fseek (fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek (fp, 0, SEEK_SET);
	return length;
}

FILE* get_requested_file_pointer(struct WebRequest *web_request, char req_file[], char local_file_location[])
{
		FILE *fp;
		char NEW_PATH[100];

		if (strcmp (web_request->http_method, "DELETE") == 0)
		{
			if (remove_status == 0)
			{
				char PATH[] = WEB_ROOT_DIR"delete_200_ok.html";
			
				fp = fopen(PATH, "rb");

				if (fp == NULL)
				{
					printf("Error opening file: %s: %d, %s\r\n", PATH, errno, strerror(errno));
				}

				http_response = HTTP_RESPONSE_DELETE;
			}
			
			else
			{
				char PATH[] = WEB_ROOT_DIR"404.html";
			
				fp = fopen(PATH, "rb");

				if (fp == NULL)
				{
					printf("Error opening file: %s: %d, %s\r\n", PATH, errno, strerror(errno));
				}

				http_response = HTTP_RESPONSE_NOT_FOUND;
			}
		}

		else if (strcmp (web_request->http_method, "PUT") == 0)
		{
				sprintf(NEW_PATH, WEB_ROOT_DIR"%s", web_request->req_file);
			
				fp = fopen(NEW_PATH, "rb");

				if (fp == NULL)
				{
					printf("Error opening file: %s: %d, %s\r\n", NEW_PATH, errno, strerror(errno));
				}
		}

		else 
		{
			// Check if requested url is "", so open index.html
			if (strcmp (local_file_location, WEB_ROOT_DIR) == 0)
			{
				char file_location[] = WEB_ROOT_DIR"index.html";
				
				fp = fopen(file_location, "rb");

				if (fp == NULL)
				{
					printf("Error opening file: %s: %d, %s\r\n", file_location, errno, strerror(errno));
				}
			}

			// Else open the requested file
			else
			{
					fp = fopen(local_file_location, "rb");

					if (fp == NULL)
					{
						printf("Error opening file: %s: %d, %s\r\n", local_file_location, errno, strerror(errno));
					}
				
			}
			
			// If the requested file is not present in web_root, then serve 404.html
			if (fp == NULL)
			{
				http_response = HTTP_RESPONSE_NOT_FOUND;
				char PATH_404[] = WEB_ROOT_DIR"404.html";

				fp = fopen(PATH_404, "rb");
				
				if (fp == NULL)
				{
					printf("Error opening file: %s: %d, %s\r\n", PATH_404, errno, strerror(errno));
				}
			}
			
			else
			{
				set_http_response(web_request, req_file);
			}
		}
		
		return fp;
}

void get_directory_files(char local_file_location[])
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir (local_file_location);
	
	// Print all the files and directories within the directory
	while ((ent = readdir (dir)) != NULL)
	{
		printf ("%s\n", ent->d_name);
		int i = 0;
		strcpy(Files_Array[i++], ent->d_name);
		
	}
	closedir (dir);
}

FILE* check_dir_index_file(char local_file_location[])
{
	FILE *fp;
	char index_file_location[200];
	sprintf(index_file_location, "%s/index.html", local_file_location);
	
	fp = fopen(index_file_location, "rb");
	
	return fp;
}

bool is_directory(char local_file_location[])
{
	struct stat sb;
	return (stat(local_file_location, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void delete_prev_existing_file(struct WebRequest *web_request, char req_file[])
{
	    char PATH[200];
		sprintf(PATH, WEB_ROOT_DIR"%s", web_request->req_file);
        
        if (access( PATH, F_OK ) != -1)
		{
    		remove(PATH); // file exists, so remove the previous file so as to create its new updated version
		}
}

int delete_requested_file(struct WebRequest *web_request, char req_file[])
{
	    char PATH[200];
        sprintf(PATH, WEB_ROOT_DIR"%s", web_request->req_file);

		int status = remove(PATH);

        if (status == 0)
        {
            printf("The requested file has been successfully deleted.\n");
			printf("\n");
        }
        
        else
        {
			printf("Unable to delete the requested file.\n");
			printf("\n");
        }

		return status;
}
