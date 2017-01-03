#include "FileUtility.h"

long get_file_size(FILE *fp)
{
	fseek (fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek (fp, 0, SEEK_SET);
	return length;
}

void read_file (FILE *fp, char content[], long length)
{
	// read the entire file content of the file pointed by fp
	fseek (fp, 0, SEEK_SET);
	fread (content, 1, length, fp);
	fclose(fp);
}

FILE* get_requested_file_pointer(char req_file[], char local_file_location[])
{
		FILE *fp;

		// check if requested url is "", so open index.html
		if (strcmp (local_file_location, WEB_ROOT_DIR) == 0)
		{
			char file_location[] = WEB_ROOT_DIR"index.html";
			fp = fopen(file_location, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", file_location, errno, strerror(errno));
			}
		}
		// else open the requested file
		else
		{		
			fp = fopen(local_file_location, "rb");

			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", local_file_location, errno, strerror(errno));
			}
		}

		// if the requested file is not present in web_root, then serve 404.html
		if (fp == NULL)
		{
			http_response = HTTP_RESPONSE_NOT_FOUND;
			char file_location[] = WEB_ROOT_DIR"404.html";
			fp = fopen(file_location, "rb");
			if (fp == NULL)
			{
				printf("Error opening file: %s: %d, %s\r\n", file_location, errno, strerror(errno));
			}
		}
		else
		{
			set_http_response(req_file);
		}
		
		return fp;
}

void get_directory_files(char local_file_location[])
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir (local_file_location);
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL)
	{
		printf ("%s\n", ent->d_name);
		int i = 0;
		strcpy(Files_Array[i++], ent->d_name);
	}
	closedir (dir);
}

bool is_directory(char local_file_location[])
{
	struct stat sb;
	return (stat(local_file_location, &sb) == 0 && S_ISDIR(sb.st_mode));
}

FILE* check_dir_index_file(char local_file_location[])
{
	FILE *fp;
	char index_file_location[200];
	sprintf(index_file_location, "%s/index.html", local_file_location);
	fp = fopen(index_file_location, "rb");
	return fp;
}
