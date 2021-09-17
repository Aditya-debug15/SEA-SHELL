#include "headers.h"
#include "display.h"
#include "echo_b.h"
#include "pwd_b.h"
#include "cd_b.h"
#include "ls_b.h"
#include "pinfo.h"
#include "repeat.h"
#include "leftover.h"
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
    if (!strcmp("exit", argv[0]))
    {
        FILE* fd=fopen(history_path,"w");
        fprintf(fd,"%d\n",latest_number);
        if(total_number<latest_number)
        {
            for(int i=0;i<latest_number;i++)
            {
                fprintf(fd,"%s",history[i]);
            }
        }
        else
        {
            for(int i=0;i<20;i++)
            {
                fprintf(fd,"%s",history[i]);
            }
        }
        fclose(fd);
        exit(0);
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
}
void signalHandler_child(int p)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid > 0)
    {

        if (!status)
            fprintf(stderr, "\n with pid %d exited normally\n", pid);
        else
            fprintf(stderr, "\n with pid %d exited abnormally\n", pid);
        dis();
        fflush(stdout);
    }
}

int main()
{
    shellInFile = dup(STDIN_FILENO);
    shellOutFile = dup(STDOUT_FILENO);
    shellpid = getpid();
    oldpwd = false;
    username = (char *)malloc(1024);
    username = getenv("USER");
    gethostname(sys_name, sizeof(sys_name));
    getcwd(tilda, sizeof(tilda));
    //printf("~ is equal to %s\n", tilda);
    char *line;
    size_t buf = 0;
    int read;
    signal(SIGCHLD, signalHandler_child);
    char* lineeo=NULL;
    for(int karna=0;karna<20;karna++)
    {
        history[karna]=(char *)malloc(1024);   
    }
    history_path=(char*)malloc(1024);
    sprintf(history_path,"%s/history.txt",tilda);
    FILE* fd=fopen(history_path,"r");
    //int filesize = lseek(fd, (off_t)0, SEEK_END);
    int filesize;
    if (fd == NULL){
        filesize=0;
    }
    latest_number=0;
    size_t readeo,len=0;
    readeo=getline(&lineeo,&len,fd);
    inital_number=atoi(lineeo);
    while ((readeo = getline(&lineeo, &len, fd)) != -1)
    {
        if(strcmp(lineeo,"\n"))
        {
            strcpy(history[latest_number],lineeo);
            latest_number++;
        }
    }
    total_number=latest_number;
    latest_number=inital_number;
    fclose(fd);
    while (1)
    {
        dis();
        read = getline(&line, &buf, stdin);
        // hello\n input hai to line mai bhi hello\n
        // \n ko \0
        strcpy(history[latest_number],line);
        latest_number++;
        latest_number%=20;
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