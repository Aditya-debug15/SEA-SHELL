#include "headers.h"
#include "display.h"
#include "echo_b.h"
#include "pwd_b.h"
#include "cd_b.h"
#include "ls_b.h"
#include "pinfo.h"
#include "repeat.h"
char *arguments[32];
void repeat(int number)
{
    if (number <= 2)
    {
        printf(":( Too few commands given\n");
    }
    else
    {
        for (int times = 0; times < atoi(argv[1]); times++)
        {
            if (!strcmp("exit", argv[0]))
            {
                exit(0);
            }
            else if (!strcmp("ls", argv[2]))
            {
                ls(3, number);
                //printf("done by me\n");
            }
            else if (!strcmp("echo", argv[2]))
            {
                echo(3, number);
                //printf("done by me\n");
            }
            else if (!strcmp("pwd", argv[2]))
            {
                pwd(2, number);
                //printf("done by me\n");
            }
            else if (!strcmp("cd", argv[2]))
            {
                cd(2, number);
                //printf("done by me\n");
            }
            else if (!strcmp("pinfo", argv[2]))
            {
                pinfo(2, number);
                //printf("done by me\n");
            }
            else
            {
                for(int i=2,j=0;i<number;i++,j++)
                {
                    arguments[j]=(char*)malloc(1024);
                    strcpy(arguments[j],argv[i]);
                }
                pid_t child_pid = fork();
                if (child_pid == 0)
                {
                    /* Never returns if the call is successful */
                    if (execvp(arguments[0], arguments) < 0)
                        printf("This won't be printed if execvp is successul\n");
                    exit(0);
                }
                else
                {
                    wait(NULL);
                }
            }
        }
    }
}