#include "headers.h"
#include "leftover.h"
// int setpgid(pid_t pid, pid_t pgid);
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
        // FORKING FAILED
        perror(":( error while forking\n");
    }
    else if (child_pid == 0)
    {
        // setpgid is used here so that child process group id changes
        // This ensures that only parent process group has access to terminal
        setpgid(0, 0);
        if (execvp(argv[0], argv) < 0)
            perror(":(");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (back == 1)
        {
            // NOW PARENT OF BACKGROUND PROCESS
            // dup2(shellOutFile, STDOUT_FILENO);
            InsertAtFront(&head,child_pid,argv[0]);
            // Adding name and pid of the process in linked list
            // Reason when process ends i need its name
            // Can't use /proc/pid/stat beacuse the process is no more
            printf("pid = %d\n", child_pid);
        }
        else
        {
            //printf("reached here\n"); debugging statement
            // Below 2 statements are used to make child (foregroung one) group as foreground group
            setpgid(child_pid, 0);
            tcsetpgrp(0, child_pid);

            // as shell will be removed from foreground so mute its call for I/O
            // else that I/O will be given to all the bg processes
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            // waiting for child to be ended 
            // WUNTRACED tells when the child is stopped due to sigstop
            waitpid(child_pid, &status, WUNTRACED);

            // Need to make the shell as foreground again
            tcsetpgrp(0, getpgid(0));
            // Giving back its signal rights
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }
}