#include "headers.h"
#include "pinfo.h"
int search2(char *pat, char *txt)
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
void pinfo(int start, int number)
{
    int pid;
    if ((number - start) == 1)
    {
        pid = (int)getpid();
    }
    else if ((number - start) == 2)
    {
        pid = atoi(argv[1]);
    }
    else
    {
        printf(":( Incorrect Number of arguments\n");
        return;
    }
    printf("pid = %d\n", pid);
    // pid pta hai
    // process state
    // memory
    // exe path
    /*
        process state 3rd line
        memory 23rd line           
        ye dono to /proc/pid/stat se nikal lunga

    */
    char path1[1024];
    char path2[1024];
    sprintf(path1, "/proc/%d/stat", pid);
    sprintf(path2, "/proc/%d/exe", pid);
    int ravi_shastri; // opener :)
    ravi_shastri = open(path1, O_RDONLY);
    if (ravi_shastri == -1)
    {
        perror(":( file not found\n");
        return;
    }
    else
    {
        char *buff = (char *)calloc(512, sizeof(char));
        read(ravi_shastri, buff, 512);
        char *process_state;
        char *virtual_memory;
        char *majboori;
        majboori = strtok(buff, " ");
        int position = 0;
        int pgr,tpgid;
        while (majboori != NULL && position < 24)
        {
            position++;
            if (position == 3)
            {
                process_state = majboori;
            }
            else if (position == 5)
            {
                pgr = atoi(majboori);
            }
            else if (position == 8)
            {
                tpgid = atoi(majboori);
            }
            else if (position == 23)
            {
                virtual_memory = majboori;
            }
            majboori = strtok(NULL, " ");
        }
        if (pgr == tpgid)
            strcat(process_state, "+");
        printf("Process state = %s\n", process_state);
        printf("Virtual Memory = %s\n", virtual_memory);
        char buf[1024];
        size_t answer = readlink(path2, buf, 1024);
        if (answer > 0)
        {
            buf[answer] = '\0';
            int p = search2(tilda, buf);
            if (p == -1)
            {
                printf("Executable Path = %s", buf);
            }
            else
            {
                p += strlen(tilda);
                printf("Executable Path = ~");
                for (int i = p; i < strlen(buf); i++)
                {
                    printf("%c", buf[i]);
                }
            }
            printf("\n");
        }
        else
        {
            printf(":( error openeing file\n");
        }
    }
    // strstr
}