#include "FileUtility.h"

void read_file(FILE *fp, char content[], long length)
{
	// Read the entire file content of the file pointed by fp
	fseek(fp, 0, SEEK_SET);
	fread(content, 1, length, fp);
	fclose(fp);
}

long get_file_size(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return length;
}

FILE *get_requested_file_pointer(struct WebRequest *web_request, char req_file[], char req_res_path[])
{
	FILE *fp;
	int length;
	char created_res_path[50];
	char *content = 0;
	char temp[] = WEB_ROOT_DIR "index.html";
	char Temp[] = CLIENT_DIR "DELETE_success.html";
	char path_404_not_found[] = WEB_ROOT_DIR "404.html";

	if (strcmp(web_request->http_method, "DELETE") == 0)
	{
		http_response = HTTP_RESPONSE_DELETE;

		if (remove_status == 0)
		{
			fp = fopen(Temp, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", Temp, errno, strerror(errno));
			}
		}

		else
		{
			http_response = HTTP_RESPONSE_NOT_FOUND;

			fp = fopen(path_404_not_found, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", path_404_not_found, errno, strerror(errno));
			}
		}
	}

	else if (strcmp(web_request->http_method, "PUT") == 0)
	{
		sprintf(created_res_path, CLIENT_DIR "%s", web_request->req_file);

		fp = fopen(created_res_path, "rb");

		if (fp == NULL)
		{
			printf("Error creating file: %s: %d, %s\r\n", created_res_path, errno, strerror(errno));

			http_response = HTTP_RESPONSE_NOT_FOUND;

			fp = fopen(path_404_not_found, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", path_404_not_found, errno, strerror(errno));
			}
		}
	}

	else if (strcmp(web_request->http_method, "HEAD") == 0)
	{
		http_response = HTTP_RESPONSE_HEAD;

		fp = fopen(req_res_path, "rb");

		if (fp == NULL)
		{
			printf("Error finding file: %s: %d, %s\r\n", req_res_path, errno, strerror(errno));

			http_response = HTTP_RESPONSE_NOT_FOUND;

			fp = fopen(path_404_not_found, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", path_404_not_found, errno, strerror(errno));
			}
		}
	}

	else if (strcmp(web_request->http_method, "TRACE") == 0)
	{
		http_response = HTTP_RESPONSE_TRACE;

		if (strcmp(web_request->req_file, "") == 0)
		{
			fp = fopen(temp, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", temp, errno, strerror(errno));
			}
		}

		else
		{
			fp = fopen(req_res_path, "rb");

			if (fp == NULL)
			{
				//http_response = HTTP_RESPONSE_NOT_FOUND;

				printf("Error opening file: %s: %d, %s\r\n", req_res_path, errno, strerror(errno));

				fp = fopen(path_404_not_found, "rb");

				if (fp == NULL)
				{
					printf("Error opening file: %s: %d, %s\r\n", path_404_not_found, errno, strerror(errno));
				}
			}
		}
	}

	// Else open the requested file
	else
	{
		fp = fopen(req_res_path, "rb");

		if (fp == NULL)
		{
			printf("Error opening file: %s: %d, %s\r\n", req_res_path, errno, strerror(errno));
		}
	}

	// If the requested file is not present in web_root, then serve 404.html
	if (fp == NULL)
	{
		http_response = HTTP_RESPONSE_NOT_FOUND;

		fp = fopen(path_404_not_found, "rb");

		if (fp == NULL)
		{
			printf("Error opening file: %s: %d, %s\r\n", path_404_not_found, errno, strerror(errno));
		}
	}

	else
	{
		set_http_response(web_request, req_file);
	}

	return fp;
}

void get_directory_files(char req_res_path[])
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(req_res_path);

	// Print all the files and directories within the directory
	while ((ent = readdir(dir)) != NULL)
	{
		printf("%s\n", ent->d_name);
		int i = 0;
		strcpy(Files_Array[i++], ent->d_name);
	}

	closedir(dir);
}

FILE *check_dir_index_file(char req_res_path[])
{
	FILE *fp;
	char index_file_path[200];
	sprintf(index_file_path, "%sindex.html", req_res_path);

	//printf("%s\r\n", index_file_path);

	fp = fopen(index_file_path, "rb");

	if (fp == NULL)
	{
		printf("Error opening file: %s: %d, %s\r\n", index_file_path, errno, strerror(errno));
	}

	return fp;
}

bool is_directory(char req_res_path[])
{
	struct stat sb;
	return (stat(req_res_path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void delete_prev_existing_file(struct WebRequest *web_request, char req_file[])
{
	char PATH[200];
	sprintf(PATH, CLIENT_DIR "%s", web_request->req_file);

	if (access(PATH, F_OK) != -1)
	{
		remove(PATH); // remove the exisiting file
	}
}

int delete_requested_file(struct WebRequest *web_request, char req_file[])
{
	char PATH[200];
	sprintf(PATH, CLIENT_DIR "%s", web_request->req_file);
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

void file_modification_status(struct WebRequest *web_request)
{
	struct stat sb;
	char PATH[200];

	if (strcmp(web_request->http_method, "DELETE") == 0 || strcmp(web_request->http_method, "PUT") == 0)
	{
		sprintf(PATH, CLIENT_DIR "%s", web_request->req_file);
	}

	else
	{
		sprintf(PATH, WEB_ROOT_DIR "%s", web_request->req_file);
	}

	strncpy(file_mod_status, "", sizeof(file_mod_status));

	if (!stat(PATH, &sb))
	{
		strftime(file_mod_status, 100, "%d/%m/%Y %H:%M:%S", localtime(&sb.st_mtime));
	}
	//printf("Last modified %s: %s\r\n", web_request->req_file, file_mod_status);
}