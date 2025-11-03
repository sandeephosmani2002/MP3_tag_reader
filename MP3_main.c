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

// Main function
int main(int argc,char* argv[])
{
    int valid = Validation_CLA(argc,argv);
    if(valid == 1)
    {
        mp3_view(argc,argv);
    }
    else if(valid == 2)
    {
        mp3_edit(argc,argv);
    }
    else if(valid == 3)
    {
        help();
    }
    return 0;
}

// Function to validate command line arguments
int Validation_CLA(int argc, char* argv[])
{
    int v = 0, file = 0, N = 0, edit_option = 0;

    // --- Check Help ---
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        return 3;
    }

    // --- Check View mode: ./a.out -v filename ---
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        v = 1;
        FILE* fb = fopen(argv[2], "r");
        if (fb != NULL)
        {
            N = 1;
            fclose(fb);
        }
    }

    // --- Check Edit mode: ./a.out -e -t/-a/-A/-y/-c/-g 'new_name' filename ---
    else if (argc == 5 && strcmp(argv[1], "-e") == 0)
    {
        file = 1;
        if ((strcmp(argv[2], "-t") == 0) || (strcmp(argv[2], "-a") == 0) ||
            (strcmp(argv[2], "-A") == 0) || (strcmp(argv[2], "-y") == 0) ||
            (strcmp(argv[2], "-c") == 0) || (strcmp(argv[2], "-g") == 0))
        {
            edit_option = 1;
            FILE* fb = fopen(argv[4], "r");
            if (fb != NULL)
            {
                N = 1;
                fclose(fb);
            }
        }
    }

    // --- Keep your original return logic ---
    if (v == 1 && N == 1)
    {
        return 1; // View mode
    }
    else if (file == 1 && edit_option == 1 && N == 1)
    {
        return 2; // Edit mode
    }
    else
    {
        printf("ERROR: ./a.out: INVALID ARGUMENTS\n");
        printf("USAGE:\n");
        printf("To view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c 'new_name' mp3filename\n");
        printf("If you want help then pass like this : ./a.out --help\n");
        return 0;
    }
}

// Help function
void help()
{
    printf("%-10s\n","USAGE:");
    printf("%-11s./a.out -e -t/-a/-A/-y/-c/-g 'new name' file.mp3\n", "");
    printf("%-11s./a.out -v file.mp3\n","");
    printf("%-11sAllows to edit a tag\n","-e");
    printf("%-11sModifies a Title tag\n","-t");
    printf("%-11sModifies an Artist tag\n","-a");
    printf("%-11sModifies an Album tag\n","-A");
    printf("%-11sModifies a Year tag\n","-y");
    printf("%-11sModifies a Comment tag\n","-c");
    printf("%-11sModifies a Genre tag\n","-g");
    printf("%-11sPrints version info\n","-v");
}

