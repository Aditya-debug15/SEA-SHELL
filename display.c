#include "headers.h"
#include "display.h"
int search(char *pat, char *txt)
{
    // naive approach to find whether "tilda"
    // exist in our current directory
    int M = strlen(pat);
    int N = strlen(txt);
    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
        {
            if (txt[i + j] != pat[j])
                break;
        }

        if (j == M)
        {
            return i;
        }
    }
    return -1;
}
void dis()
{
    getcwd(curr_dir,sizeof(curr_dir));
    printf("<%s@%s:", username, sys_name);
    int p=search(tilda,curr_dir);
    if(p==-1)
    {
        printf("%s>",curr_dir);
    }
    else
    {
        p+=strlen(tilda);
        printf("~");
        for(int i=p;i<strlen(curr_dir);i++)
        {
            printf("%c",curr_dir[i]);
        }
        printf(">");
    }
    // logic for dir
}