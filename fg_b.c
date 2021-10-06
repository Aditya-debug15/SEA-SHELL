#include "headers.h"
#include "fg_b.h"
#include "linkedfgs.h"
void fg(int start, int num_arg)
{
    if (num_arg != 2)
    {
        printf(":( Incorrect number of arguments\n");
        return;
    }
    int job_num = atoi(argv[1]);
    int pid_job = pidfromjob(head, job_num);
    if (pid_job < 0)
    {
        printf(":( Invalid Job number\n");
        return;
    }
    // remove kardo list se
    removefromlist_withoutprinting(&head,pid_job);
    // as shell will be removed from foreground so mute its call for I/O
    // else that I/O will be given to all the bg processes
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, getpgid(pid_job));
    if (kill(pid_job, SIGCONT) < 0)
    {
        perror("Error");
    }
    // waitpid(pid, NULL, 0);
    waitpid(pid_job,NULL, WUNTRACED);   
    tcsetpgrp(0, getpgid(0));
    // Giving back its signal rights
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}