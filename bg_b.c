#include "headers.h"
#include "bg_b.h"
#include "linkedfgs.h"
void bg(int start, int num_arg)
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
    // stop -> running karna
    // this means list se remove karne ki zaroort nahi
    // signal continue ka bhej do
    // sig job_num 18 ne karna tha
    if (kill(pid_job, SIGCONT) < 0)
    {
        perror("");
    }
}