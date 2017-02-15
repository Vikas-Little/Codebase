
// C Program to print the source code of a Web Page on the terminal

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

void get_web_page_content(char title[], char main_content[], struct WebLink links[], char web_page_content[])
{		
	struct WebPage new_page;
	strcpy (new_page.title, title);

	sprintf (new_page.page_header, 	"<head>"
										"<link href=\"style.css\" rel=\"stylesheet\">"
										"<script src=\"script.js\" type=\"text/javascript\"></script>"
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

int main()
{
    char web_page_content[4000];	
	char main_content[] = "This is the content";
	struct WebLink links[4];		
	
	strcpy (links[0].link_name, "Google");
	strcpy (links[0].link_address, "http://www.google.com");
	strcpy (links[1].link_name, "Planys");
	strcpy (links[1].link_address, "http://www.planystech.com");
	strcpy (links[2].link_name, "UPES");
	strcpy (links[2].link_address, "http://www.upes.ac.in");
	strcpy (links[3].link_name, "XYZ");
	strcpy (links[3].link_address, "http://www.upes.ac.in");

	get_web_page_content("Web Page Title", main_content, links, web_page_content);

	printf("Web page is %lu bytes:\n%s\n", sizeof(web_page_content), web_page_content);

	return 0;
}
