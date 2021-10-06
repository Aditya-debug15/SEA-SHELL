#include "headers.h"
#include "display.h"
#include "execute.h"
#include "history.h"
#include "pipe_b.h"
#include "signal_b.h"
void signalHandler_child(int p)
{
    int status;
    // Using both WNOHANG and WUNTRACED
    // so that even if the background process is stopped or exited i will have the signal
    pid_t pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
    if (pid > 0)
    {
        int pr = presentinlist(head, pid);
        printf("\n");
        if (pr && (WIFEXITED(status) || WIFSIGNALED(status)))
        {
            removefromlist(&head, pid);
            if (!status)
                printf(" with pid %d exited normally\n", pid);
            else
                printf(" with pid %d exited abnormally\n", pid);
            dis();
            fflush(stdout);
        }
        else if (pr)
        {
            printf("task with pid %d is stopped\n", pid);
            dis();
            fflush(stdout);
        }
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
    signal(SIGTSTP, signal_for_cz);
    signal(SIGINT, signal_for_cc);
    readfromhistory();
    head = CreateEmptyList();
    back_count = 0;
    process_pid = 0;
    // till here so why not new .c and .h file
    while (1)
    {
        dis();
        read = getline(&line, &buf, stdin);
        if (read == -1)
        {
            // Ctrl + D
            printf("\n");
            EmptyList(&head);
            writetohistory();
        }
        // hello\n input hai to line mai bhi hello\n
        // \n ko \0
        //printf("reached here\n");
        int cheker;
        if (latest_number == 0)
        {
            cheker = 19;
        }
        else
        {
            cheker = latest_number - 1;
        }
        if (strcmp(line, history[cheker]) && strcmp(line, "\n"))
        {
            strcpy(history[latest_number], line);
            latest_number++;
            latest_number %= 20;
        }
        line[read - 1] = '\0';
        //printf("reached here after line read\n");
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
        // case 1 <,>,>>
        // case 2 |
        // case 3 <,|
        // acse 4 nothing
        bool condition2 = false;
        for (int j = 0; j < number_of_task; j++)
        {
            for (int i = 0; i < strlen(extra_task[j]); i++)
            {
                if (extra_task[j][i] == '|')
                {
                    condition2 = true;
                    break;
                }
            }
            if (condition2)
            {
                // case 3
                pipe_b(j);
            }
            else
            {
                execute(j);
            }
        }
    }
}