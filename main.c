#include "headers.h"
#include "display.h"
#include "echo_b.h"
#include "pwd.h"
#include "cd_b.h"
#include "ls_b.h"
void execute(int task_id)
{
    int i = 0;
    argv[0] = strtok(extra_task[task_id], " \t");
    while (argv[i] != NULL)
    {
        //printf("%s\n",argv[i]);
        i++;
        argv[i] = strtok(NULL, " \t");
    }
    if(!strcmp("exit",argv[0]))
    {
        exit(0);
    }
    else if(!strcmp("ls",argv[0]))
    {
        ls(i);
        printf("done by me");
    }
    else if (!strcmp("echo", argv[0]))
    {
        echo(i);
        //printf("done by me\n");
    }
    else if (!strcmp("pwd", argv[0]))
    {
        pwd(i);
        //printf("done by me\n");
    }
    else if(!strcmp("cd",argv[0]))
    {
        cd(i);
        printf("done by me\n");
    }

    else
    {
        pid_t child_pid = fork();
        if (child_pid == 0)
        {
            /* Never returns if the call is successful */
            if (execvp(argv[0], argv) < 0)
                printf("This won't be printed if execvp is successul\n");
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
}

int main()
{
    oldpwd=false;
    username = (char *)malloc(1024);
    username = getenv("USER");
    gethostname(sys_name, sizeof(sys_name));
    getcwd(tilda, sizeof(tilda));
    //printf("~ is equal to %s\n", tilda);
    char *line;
    size_t buf = 0;
    int read;
    while (1)
    {
        dis();
        read = getline(&line, &buf, stdin);
        // hello\n input hai to line mai bhi hello\n
        // \n ko \0
        line[read - 1] = '\0';
        // break it wrt ;
        // to get the number of commands
        // break the command wrt to '' '\t'
        // strtok
        int number_of_task = 0;
        task = strtok(line, ";");
        while (task != NULL)
        {
            extra_task[number_of_task] = task;
            number_of_task++;
            //printf("%s\n",task);
            task = strtok(NULL, ";");
        }
        for (int j = 0; j < number_of_task; j++)
        {
            execute(j);
        }
    }
}