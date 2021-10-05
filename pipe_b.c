#include "headers.h"
#include "pipe_b.h"
#include "execute.h"

void pipe_b(int task_number)
{
    // tokenize wrt to |
    // extra_task[task_number] ke maje lene
    int num_pipes = 0;
    int back = 0;
    char* pipes[32];
    // initial check kardo
    int count_danda=0;
    for(int i=0;i<strlen(extra_task[task_number]);i++)
    {
        if(extra_task[task_number][i]=='|')
        {
            count_danda++;
        }
    }
    pipes[0] = strtok(extra_task[task_number], "|");
    while (pipes[num_pipes] != NULL)
    {
        //printf("%s\n",argv[i]);
        num_pipes++;
        pipes[num_pipes] = strtok(NULL, "|");
    }
    if(num_pipes != count_danda+1)
    {
        printf(":( Error incorrect arguments\n");
        return;
    }
    // jitne dande utna pipes khole lete
    int storage[count_danda][2];
    for(int i=0;i<=count_danda;i++)
    {
        if(pipe(storage[i])<0)
        {
            perror(":(");
        }
        if(i==0)
        {
            // stdin hi hai input
            int outfile=dup(STDOUT_FILENO);
            dup2(storage[i][1],STDOUT_FILENO);
            close(storage[i][1]);
            execute_withstring(pipes[i]);
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        else if(i==count_danda)
        {
            // stdout hi hai output
            int infile=dup(STDIN_FILENO);
            dup2(storage[i-1][0],STDIN_FILENO);
            close(storage[i-1][0]);
            execute_withstring(pipes[i]);
            dup2(infile,STDIN_FILENO);
            close(infile);
        }
        else{
            int infile=dup(STDIN_FILENO);
            int outfile=dup(STDOUT_FILENO);
            dup2(storage[i-1][0],STDIN_FILENO);
            dup2(storage[i][1],STDOUT_FILENO);
            close(storage[i-1][0]);
            close(storage[i][1]);
            execute_withstring(pipes[i]);
            dup2(infile,STDIN_FILENO);
            dup2(outfile, STDOUT_FILENO);
            close(infile);
            close(outfile);
        }
    }
}