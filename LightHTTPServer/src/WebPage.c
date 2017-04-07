#include "WebPage.h"

void get_web_page_content(char title[], char main_content[], struct WebLink links[], char web_page_content[])
{		
	struct WebPage new_page;
	strcpy (new_page.title, title);

	sprintf (new_page.page_header, 	"<head>"
										"<link href=\"/style.css\" rel=\"stylesheet\">"
										"<script src=\"/script.js\" type=\"text/javascript\"></script>"
										"<title>%s</title>"
				  					"</head>", new_page.title);

	sprintf(new_page.nav_bar, 	"<body>"
									"<div id=\"nav\">");

	int i = 0;
	for (; i < 4; i++)
	{
			strcpy (new_page.navigation_links[i].link_name, links[i].link_name);
			strcpy (new_page.navigation_links[i].link_address, links[i].link_address);

			char temp_str[200];
			sprintf(temp_str,	"<div>"
										"<a href=\"%s\">%s</a>"
								  		"</div>", new_page.navigation_links[i].link_address, new_page.navigation_links[i].link_name);
			strcat(new_page.nav_bar, temp_str);
	}
	
	strcat(new_page.nav_bar, 	"</div>");
	
	sprintf(new_page.content, "<div id=\"content\">%s</div>", main_content);

	sprintf(new_page.footer,		"<div id=\"footer\">"
										"Running <strong>LightHTTPServer v1.0</strong> by <strong><i>Vikash Upadhyay</i></strong>"
									"</div>"
								"</body>"
							"</html>");

	strcpy(web_page_content, "<!DOCTYPE html> <html>");
	strcat(web_page_content, new_page.page_header);
	strcat(web_page_content, new_page.nav_bar);
	strcat(web_page_content, new_page.content);
	strcat(web_page_content, new_page.footer);
}