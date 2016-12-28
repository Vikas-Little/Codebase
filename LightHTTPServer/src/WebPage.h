#ifndef _WEBPAGE_H
#define _WEBPAGE_H

#include <stdio.h>
#include <string.h>

struct WebLink
{
	char link_name[50];
	char link_address[200];
};

struct WebPage
{
	char page_header[500];
	char nav_bar[500];
	char title[50];
	struct WebLink navigation_links[4];
	char content[2000];
	char footer[200];
};
#endif