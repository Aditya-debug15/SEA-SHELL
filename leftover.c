#include "headers.h"
#include "leftover.h"
void leftover(int number, int back)
{
    //printf("reached here\n");
    int status;
    int j = 0;
    for (int i = 0; i < number; i++)
    {
        if (strcmp(argv[i], ""))
        {
            argv[j++] = argv[i];
        }
    }
    argv[j] = 0;
    // execpv ko bahut dikkat hai spaces se aur ek space to hoga jab mai & hatunga
    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        printf(":( error while forking\n");
    }
    else if (child_pid == 0)
    {
        setpgid(0, 0);
        if (execvp(argv[0], argv) < 0)
            printf("This won't be printed if execvp is successul\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (back == 1)
        {
            dup2(shellOutFile, STDOUT_FILENO);
            InsertAtFront(&head,child_pid,argv[0]);
            printf("pid = %d\n", child_pid);
        }
        else
        {
            //printf("reached here\n");
            // make the forground process group foreground
            setpgid(child_pid, 0);
            tcsetpgrp(0, child_pid);

            // as shell will be removed from foreground so mute its call for I/O
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            waitpid(child_pid, &status, WUNTRACED);

            // shell to foreground now
            tcsetpgrp(0, getpgid(0));

            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }
}