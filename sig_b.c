#include "headers.h"
#include "sig_b.h"
#include "linkedfgs.h"

void sig(int start,int num_arg)
{
    if(num_arg!=3)
    {
        printf(":( Incorrect Number of Arguments\n");
        return;
    }
    else{
        int job_input=atoi(argv[1]);
        int signal_input=atoi(argv[2]);
        //printf("%d %d",job_input,signal_input);
        // get pid 
        // error checking
        int pid_job=pidfromjob(head,job_input);
        if(pid_job==-1)
        {
            printf(":( ERROR : With the given job number we don't have a Process \n");
            return;
        }
        else
        {
            //printf("%d ko signal dunga %d\n",pid_job,signal_input);
            if(kill(pid_job,signal_input)<0)
            {
                perror("");
            }
        }
    }
}