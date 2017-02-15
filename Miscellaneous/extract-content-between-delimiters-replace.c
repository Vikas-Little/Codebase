
// C Program to extract the content betweeen two delimiters and to replace the extracted content with some other content

#include <stdio.h>
#include <string.h>

void str_replace(char *s)
{
	char buffer[1000];
	strncpy (buffer, "", sizeof (buffer));
	char *insert_point = buffer;
	char start_del[] = "{{";
	char end_del[] = "}}"; 
	char temp[100];
	char temp_one[1000];
    char *p, *q;
	char replace_by_text_first[] = "replacing \"allow\" successful";
	char replace_by_text_second[] = "replacing \"pass additional\" successful";
	char replace_by_text_third[] = "replacing \"request\" successful";
	
	while (1)
	{
		strncpy (temp, "", sizeof (temp));
		strncpy (temp_one, "", sizeof (temp_one));
		p = strstr(s, start_del); 
		
		if (p == NULL)
		{		
			strcpy(insert_point, s);
			break;
		} 
		
		q = p + strlen(start_del); strcpy(temp_one, q);
		
		int tdx = 0, idx = 0;
		while(temp_one[idx] != '}')
		{
			temp[tdx++] = temp_one[idx];
			idx++;
		}

		memcpy(insert_point, s, q - s);
		insert_point += q - s;
		
		if ( strcmp (temp, "allow") == 0 )
		{
			strcpy(insert_point, replace_by_text_first);
			insert_point += strlen(replace_by_text_first);
		}
		else if ( strcmp (temp, "pass additional") == 0 )
		{
			strcpy(insert_point, replace_by_text_second);
			insert_point += strlen(replace_by_text_second);
		}
		else if ( strcmp (temp, "request") == 0 )
		{
			strcpy(insert_point, replace_by_text_third);
			insert_point += strlen(replace_by_text_third);
		}
		
		strcpy(insert_point, end_del);
		insert_point += strlen(end_del);
		s += q -s + strlen(temp) + strlen(end_del);
	}
	
	puts(buffer);
}

int main()
{
	char content[] = "HTTP headers {{allow}} the client and the server to {{pass additional}} information with the {{request}} or the response.";
	str_replace(content);
	return 0;
}
