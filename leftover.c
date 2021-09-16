#include "headers.h"
#include "leftover.h"

void leftover(int number, int back)
{
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
        if (execvp(argv[0], argv) < 0)
            printf("This won't be printed if execvp is successul\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (back == 1)
        {
            printf("pid = %d\n", child_pid);
        }
        else
        {
            int status;
            waitpid(child_pid, &status, WUNTRACED);
        }
    }
}