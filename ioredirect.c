#include "headers.h"
#include "ioredirect.h"

int ioredirect(int number_of_arguments)
{
    // printf("reached here\n");
    int n = number_of_arguments;
    int i = 0, j = 0;
    char inname[1024];
    char outname[1024];
    bool inpresent = false;
    bool outpresent = false;
    bool append = false;
    for (; j < number_of_arguments - 1; j++)
    {
        if (!strcmp(argv[j], "<"))
        {
            inpresent = true;
            j++;
            strcpy(inname, argv[j]);
            n -= 2;
        }
        else if (!strcmp(argv[j], ">"))
        {
            outpresent = true;
            j++;
            strcpy(outname, argv[j]);
            n -= 2;
        }
        else if (!strcmp(argv[j], ">>"))
        {
            outpresent = true;
            append = true;
            j++;
            strcpy(outname, argv[j]);
            n -= 2;
        }
        else
        {
            strcpy(argv[i], argv[j]);
            i++;
        }
    }
    if (inpresent)
    {
        int input_file;
        input_file = open(inname, O_RDONLY);
        if (input_file < 0)
        {
            perror(":(");
            return -1;
        }
        else
        {
            dup2(input_file, STDIN_FILENO);
            close(input_file);
        }
    }
    if(outpresent && !append)
    {
        int outfile;
        outfile = open(outname,O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile < 0)
        {
            perror(":(");
            return -1;
        }
        else
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
    }
    else if(outpresent && append)
    {
        int outfile;
        outfile = open(outname,O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (outfile < 0)
        {
            perror(":(");
            return -1;
        }
        else
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
    }
    /*for (int e = 0; e < n; e++)
    {
        printf("%s ", argv[e]);
    }
    printf("\n");*/
    return n;
}