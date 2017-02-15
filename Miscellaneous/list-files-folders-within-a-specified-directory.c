
// C program to print all the files and directories within a specified directory

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main()
{
   DIR *dir;

   struct dirent *ent;

	if ((dir = opendir ("/home/vikash/Main-Project")) != NULL)
	{
		  while ((ent = readdir (dir)) != NULL)	/* read directory using readdir() function */
		  {
		  	printf ("%s\n", ent->d_name); /* print all the files and directories within directory */
		  }
		  printf("\n");
	  	  closedir (dir);
	}

	/* If directory is not present then, print the error message */
	else
	{
		  /* could not open directory */
		  perror ("Could not open directory!");
		  exit(1);
	}
}
