#include "headers.h"
#include "jobs_b.h"

void jobs(int start, int num_arguments)
{
    bool flag_r = false;
    bool flag_s = false;
    int count_flags = 0;
    for (int i = start; i < num_arguments; i++)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); j++)
            {
                if (argv[i][j] == 'r')
                {
                    flag_r = true;
                }
                else if (argv[i][j] == 's')
                {
                    flag_s = true;
                }
            }
            count_flags++;
        }
    }
    //printf("%d %d\n",num_arguments,count_flags);
    if (num_arguments == 1 || ((num_arguments == (count_flags+ 1)) && flag_r &&flag_s))
    {
        // no flags wala case
        // print all
        List walk = head;
        while (walk != NULL)
        {
            // status nikalna hai
            // All processes with status T are Stopped. Running is R and S
            int pid = walk->pid;
            char path1[1024];
            sprintf(path1, "/proc/%d/stat", pid);
            int ravi_shastri; // opener :)
            ravi_shastri = open(path1, O_RDONLY);
            if (ravi_shastri == -1)
            {
                walk = walk->next;
            }
            else
            {
                char *buff = (char *)calloc(512, sizeof(char));
                read(ravi_shastri, buff, 512);
                char *process_state;
                char *majboori;
                majboori = strtok(buff, " ");
                int position = 0;
                while (majboori != NULL && position < 4)
                {
                    position++;
                    if (position == 3)
                    {
                        process_state = majboori;
                    }
                    majboori = strtok(NULL, " ");
                }
                if (!strcmp(process_state, "R") || !strcmp(process_state, "S"))
                {
                    strcpy(process_state, "Running");
                }
                else
                {
                    strcpy(process_state, "Stopped");
                }
                printf("[%d] %s %s [%d]\n", (walk)->job_num, process_state, walk->command, walk->pid);
                walk = (walk)->next;
            }
        }
    }
    else if(num_arguments == (count_flags + 1))
    {
        // flags wala case
        // print all
        List walk = head;
        while (walk != NULL)
        {
            // status nikalna hai
            // All processes with status T are Stopped. Running is R and S
            int pid = walk->pid;
            char path1[1024];
            char path2[1024];
            sprintf(path1, "/proc/%d/stat", pid);
            sprintf(path2, "/proc/%d/exe", pid);
            int ravi_shastri; // opener :)
            ravi_shastri = open(path1, O_RDONLY);
            if (ravi_shastri == -1)
            {
                walk = walk->next;
            }
            else
            {
                char *buff = (char *)calloc(512, sizeof(char));
                read(ravi_shastri, buff, 512);
                char *process_state;
                char *majboori;
                majboori = strtok(buff, " ");
                int position = 0;
                while (majboori != NULL && position < 4)
                {
                    position++;
                    if (position == 3)
                    {
                        process_state = majboori;
                    }
                    majboori = strtok(NULL, " ");
                }
                if ((!strcmp(process_state, "R") || !strcmp(process_state, "S")) && flag_r)
                {
                    strcpy(process_state, "Running");
                    printf("[%d] %s %s [%d]\n", (walk)->job_num, process_state, walk->command, walk->pid);
                }
                else if(!strcmp(process_state,"T") && flag_s)
                {
                    strcpy(process_state, "Stopped");
                    printf("[%d] %s %s [%d]\n", (walk)->job_num, process_state, walk->command, walk->pid);
                }
                walk = (walk)->next;
            }
        }
    }
    else{
        printf(":( Incorrect number of arguments\n");
    }
}