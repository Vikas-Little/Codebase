#ifndef _FILEUTILITY_H
#define _FILEUTILITY_H

#include "LightHTTPServer.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

extern int http_response;

void read_file(FILE *, char content[], long );

long get_file_size(FILE *);

FILE* get_requested_file_pointer(struct WebRequest *, char req_file[], char local_file_location[]);

void get_directory_files(char local_file_location[]);

FILE* check_dir_index_file(char local_file_location[]);

bool is_directory(char local_file_location[]);

void delete_prev_existing_file(struct WebRequest *, char req_file[]);

int delete_requested_file(struct WebRequest *, char req_file[]);

#endif