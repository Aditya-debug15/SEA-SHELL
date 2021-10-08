#include "headers.h"
#include "execute.h"
#include "replay.h"

void replay(int start,int num_arg)
{
    int inter;
    int total_time;
    char comm[1024];
    for(int i=start;i<num_arg;i++)
    {
        if(argv[i][0]=='-')
        {
            if(!strcmp(argv[i],"-interval"))
            {
                i++;
                inter=atoi(argv[i]);
            }
            if(!strcmp(argv[i],"-period"))
            {
                i++;
                total_time=atoi(argv[i]);
            }
            if(!strcmp(argv[i],"-command"))
            {
                i++;
                strcpy(comm,argv[i]);
                i++;
                while(i<num_arg)
                {
                    if(argv[i][0]!='-')
                    {
                        strcat(comm, " ");
                        strcat(comm,argv[i]);
                    }
                    else if(argv[i][0]=='-')
                    {
                        i--;
                        break;
                    }
                    i++;
                }
            }
        }
    }
    printf("%d %d %s\n",inter,total_time,comm);
    int exe_times=total_time/inter;
    int last_wait=total_time-(inter*exe_times);
    printf("%d %d\n",exe_times,last_wait);
    for(int i=0;i<exe_times;i++)
    {
        sleep(inter);
        printf("operation : %d\n",i+1);
        char esakyonhai[1024];
        strcpy(esakyonhai,comm);
        execute_withstring(esakyonhai);
    }
    if(last_wait>0)
    {
        sleep(last_wait);
    }
}