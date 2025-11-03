/*
NAME = SANDEEP HOSMANI
DATE = 20/10/25
DESCRIPTION = "PROJECT IS AN MP3 TAG EDITOR"
              1. This project is an MP3 Tag Editor and Viewer developed in C language.

              2. It can read and display ID3v2 tags such as Title, Artist, Album, Year, and Comments.

              3. Users can edit specific tags (like -t, -a, -A, -y, -c) and update them with new values.

              4. The program performs command-line argument validation to ensure correct usage.

              5. It creates a temporary MP3 file to safely apply and save the edited metadata.

              6. A help option (--help) is provided to guide users on available commands and usage formats.
*/



#include<stdio.h>
#include "MP3_header.h"
#include<string.h>
#include<stdlib.h>

// Function to edit specific MP3 ID3 tags
void mp3_edit(int argc, char* argv[])
{
    // Safety checks
    if (argc < 5)
    {
        printf("ERROR: Missing arguments for edit mode.\n");
        printf("Usage: ./a.out -e -a/-t/-A/-y/-c 'new_value' filename.mp3\n");
        return;
    }

    char *option = argv[2];       // e.g., "-a"
    char *new_value = argv[3];    // e.g., "New Artist"
    char *filename = argv[4];     // e.g., "song.mp3"


    // Open source and temporary files
    FILE *fb = fopen(filename, "r");
    FILE *gb = fopen("temp.mp3", "w");

    if (fb == NULL)
    {
        printf("ERROR: Cannot open file %s\n", filename);
        return;
    }

    if (gb == NULL)
    {
        printf("ERROR: Cannot create temp.mp3\n");
        fclose(fb);
        return;
    }
    // Copy MP3 header (first 10 bytes) to new file
    char header[10];
    fread(header, sizeof(header), 1, fb);
    fwrite(header, sizeof(header), 1, gb);

    // Identify which tag to modify
    char target_tag[5];
    if (!strcmp(option, "-a"))
        strcpy(target_tag, "TPE1");   // Artist
    else if (!strcmp(option, "-t"))
        strcpy(target_tag, "TIT2");   // Title
    else if (!strcmp(option, "-A"))
        strcpy(target_tag, "TALB");   // Album
    else if (!strcmp(option, "-y"))
        strcpy(target_tag, "TYER");   // Year
    else if (!strcmp(option, "-c"))
        strcpy(target_tag, "COMM");   // Comment
    else
    {
        printf("ERROR: Unknown tag option %s\n", option);
        fclose(fb);
        fclose(gb);
        return;
    }


   // Loop through tags and modify the selected one
   char tag[5];
   while (fread(tag, 4, 1, fb) == 1)
   { 
 

	tag[4]='\0';

	// If tag matches the one to be edited
	if(!(strcmp(tag,target_tag)))
	{
   		fwrite(tag,4,1,gb);
    		int size;
    		fread(&size,sizeof(size),1,fb);
    		int size_1 = convert(size);


		// Calculate and write new tag size
    		int new_tag_len = strlen(argv[3])+1;
    		int new1_size = convert(new_tag_len);
    		fwrite(&new1_size,sizeof(new1_size),1,gb);

		// Skip 3 bytes of flag info
		fseek(gb,3,SEEK_CUR);
   		fwrite(argv[3],new_tag_len-1,1,gb);


		// Skip old tag content in original file + also the flag and null of 3 bytes
    		fseek(fb,size_1+2,SEEK_CUR);
		break;
	}
	else
	{

		// Copy unmodified tags as-is
		fwrite(tag,4,1,gb);
		int size2;
		fread(&size2,sizeof(size2),1,fb);
		fwrite(&size2,sizeof(size2),1,gb);
		fseek(fb,3,SEEK_CUR);
		fseek(gb,3,SEEK_CUR);
		int size2_1 = convert(size2);
		char content[size2_1-1];
		fread(content,sizeof(content),1,fb);
		fwrite(content,sizeof(content),1,gb);
		
	
		
	}
	
  }


  // Copy remaining part of MP3 file
  unsigned ch;
  while((ch = getc(fb))!=EOF)
  {
	  fputc(ch,gb);
	  
  }
  printf("Tag %s update successfully.\n",target_tag);


  //Files can be renamed or replaced if needed
  int s = strlen(argv[4]);
  char file[s];
  strcpy(file,argv[4]); 
  remove(argv[4]);
  rename("temp.mp3",file);
  
  fclose(fb);
  fclose(gb);

}
