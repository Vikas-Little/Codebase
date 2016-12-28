#ifndef _FILEUTILITY_H
#define _FILEUTILITY_H

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

extern int http_response;

long get_file_size(FILE *);

void read_file (FILE *, char content[], long );

FILE* get_requested_file_pointer(char req_file[], char local_file_location[]);

void get_directory_files(char local_file_location[]);

bool is_directory(char local_file_location[]);

FILE* check_dir_index_file(char local_file_location[]);

#endif