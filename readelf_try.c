#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


main (int argc, char *argv[])
{
	unsigned char s[16];
	int plc = 0, i, j;
	FILE *fp;

	if (argc != 2)
    {
		printf ("usage: ./readobj <obj_file_name>");
		exit(1);
	}
        //opening file in binary format
	fp = fopen (argv[1], "rb");

	while (!feof (fp))
    {

		for (i=0; i<16; i++)
        {
			s[i] = fgetc (fp);
			if (feof (fp)) break; 
		}
		
		printf ("%04XH : ", plc);
		plc = plc + 16;

		for (j=0; j<i; j++)
        {
			printf ("%02X ", s[j]);
		}
        for(j=i;j<16;j++)printf("%3s"," ");//incase of alignment
		printf ("%5s"," ");
		for (j=0; j<i; j++)
            {
            if (isprint ((char)s[j]))
                    printf ("%c", s[j]);//incase of graphic characters
                else printf (".");//incase of non-graphic characters
            }
        
		printf ("\n");//newline
	}


	fclose (fp);
}
