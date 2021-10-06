#include "headers.h"
#include "execute.h"
#include "echo_b.h"
#include "pwd_b.h"
#include "cd_b.h"
#include "ls_b.h"
#include "pinfo.h"
#include "repeat.h"
#include "leftover.h"
#include "history.h"
#include "ioredirect.h"
#include "jobs_b.h"
#include "sig_b.h"
#include "fg_b.h"
#include "bg_b.h"
void execute(int task_id)
{
    int i = 0;
    int back = 0;
    argv[0] = strtok(extra_task[task_id], " \t");
    while (argv[i] != NULL)
    {
        //printf("%s\n",argv[i]);
        i++;
        argv[i] = strtok(NULL, " \t");
    }
    for (int j = 0; j < i; j++)
    {
        if (!strcmp("&", argv[j]))
        {
            argv[j] = "";
            back = 1;
            break;
        }
    }
    for(int j=0;j<i;j++)
    {
        if(!strcmp(">",argv[j]) || !strcmp("<",argv[j]) || !strcmp(">>",argv[j]))
        {
            int checker=ioredirect(i);
            if(checker==-1)
            {
                return;
            }
            i=checker;
        }
    }
    if (!strcmp("exit", argv[0]))
    {
        EmptyList(&head);
        writetohistory();
    }
    else if (!strcmp("ls", argv[0]))
    {
        ls(1, i);
        //printf("done by me\n");
    }
    else if (!strcmp("echo", argv[0]))
    {
        echo(1, i);
        //printf("done by me\n");
    }
    else if (!strcmp("pwd", argv[0]))
    {
        pwd(0, i);
        //printf("done by me\n");
    }
    else if (!strcmp("cd", argv[0]))
    {
        cd(0, i);
        //printf("done by me\n");
    }
    else if (!strcmp("pinfo", argv[0]))
    {
        pinfo(0, i);
        //printf("done by me\n");
    }
    else if (!strcmp("repeat", argv[0]))
    {
        repeat(i);
    }
    else if (!strcmp("history", argv[0]))
    {
        commandhistory(i);
    }
    else if(!strcmp("jobs",argv[0]))
    {
        jobs(0,i);
    }
    else if(!strcmp("sig",argv[0]))
    {
        sig(0,i);
    }
    else if(!strcmp("fg",argv[0]))
    {
        fg(0,i);
    }
    else if(!strcmp("bg",argv[0]))
    {
        bg(0,i);
    }
    // For debugging purpose
    else if (!strcmp("P", argv[0]))
    {
        PrintList(head);
    }
    else
    {
        leftover(i, back);
        /*pid_t child_pid = fork();
        if (child_pid < 0)
        {
            printf(":( error while forking\n");
        }
        else if (child_pid == 0)
        {
            if (execvp(argv[0], argv) < 0)
                printf("This won't be printed if execvp is successul\n");
            exit(EXIT_FAILURE);
        }
        if (back == 1)
        {
            printf("pid = %d\n", child_pid);
        }
        else
        {
            int status;        
            waitpid(child_pid, &status, WUNTRACED);
        }*/
    }
    dup2(shellInFile,STDIN_FILENO);
    dup2(shellOutFile,STDOUT_FILENO);
}

void execute_withstring(char* s)
{
    int i = 0;
    int back = 0;
    argv[0] = strtok(s, " \t");
    while (argv[i] != NULL)
    {
        //printf("%s\n",argv[i]);
        i++;
        argv[i] = strtok(NULL, " \t");
    }
    for (int j = 0; j < i; j++)
    {
        if (!strcmp("&", argv[j]))
        {
            argv[j] = "";
            back = 1;
            break;
        }
    }
    for(int j=0;j<i;j++)
    {
        if(!strcmp(">",argv[j]) || !strcmp("<",argv[j]) || !strcmp(">>",argv[j]))
        {
            int checker=ioredirect(i);
            if(checker==-1)
            {
                return;
            }
            i=checker;
        }
    }
    if (!strcmp("exit", argv[0]))
    {
        writetohistory();
        EmptyList(&head);
    }
    else if (!strcmp("ls", argv[0]))
    {
        ls(1, i);
        //printf("done by me\n");
    }
    else if (!strcmp("echo", argv[0]))
    {
        echo(1, i);
        //printf("done by me\n");
    }
    else if (!strcmp("pwd", argv[0]))
    {
        pwd(0, i);
        //printf("done by me\n");
    }
    else if (!strcmp("cd", argv[0]))
    {
        cd(0, i);
        //printf("done by me\n");
    }
    else if (!strcmp("pinfo", argv[0]))
    {
        pinfo(0, i);
        //printf("done by me\n");
    }
    else if (!strcmp("repeat", argv[0]))
    {
        repeat(i);
    }
    else if (!strcmp("history", argv[0]))
    {
        commandhistory(i);
    }
    else if(!strcmp("jobs",argv[0]))
    {
        jobs(0,i);
    }
    // For debugging purpose
    else if (!strcmp("P", argv[0]))
    {
        PrintList(head);
    }
    else
    {
        leftover(i, back);
        /*pid_t child_pid = fork();
        if (child_pid < 0)
        {
            printf(":( error while forking\n");
        }
        else if (child_pid == 0)
        {
            if (execvp(argv[0], argv) < 0)
                printf("This won't be printed if execvp is successul\n");
            exit(EXIT_FAILURE);
        }
        if (back == 1)
        {
            printf("pid = %d\n", child_pid);
        }
        else
        {
            int status;        
            waitpid(child_pid, &status, WUNTRACED);
        }*/
    }
    dup2(shellInFile,STDIN_FILENO);
    dup2(shellOutFile,STDOUT_FILENO);
}
