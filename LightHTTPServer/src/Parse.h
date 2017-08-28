#ifndef _PARSE_H
#define _PARSE_H

#include "LightHTTPServer.h"
#include <stdio.h>
#include <string.h>

void parse_field_data(struct WebRequest *, struct WebForm *, char[], char[]);

int parse_form_field(char *, char *, char *, int);

void parse_query_string(struct WebRequest *, struct WebForm *);

void parse_request_line(struct WebRequest *, char *, char *);

void parse_request_message_line(char *, struct WebRequest *, struct WebForm *);

void parse_request(struct WebRequest *, char *, struct WebForm *);

void print_request(struct WebRequest *, struct WebForm *);

#endif