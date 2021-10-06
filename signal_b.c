#include "headers.h"
#include "signal_b.h"
#include "display.h"
#include "linkedfgs.h"
void signal_for_cc(int p)
{
    // foreground mai process run kar rha hai to
    pid_t process = process_pid;
    if (process > 0)
    {
        kill(process, p);
        printf("\n");
        fflush(stdout);
    }
    else
    {
        // no need to send signal
        printf("\n");
        dis();
        fflush(stdout);
    }
}

void signal_for_cz(int p)
{
    if (process_pid > 0 && process_pid != getpid())
    {
        raise(SIGTSTP);
    }
    printf("Here\n");
    printf("\n");
    dis();
    fflush(stdout);
}