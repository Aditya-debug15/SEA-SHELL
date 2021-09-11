#include"headers.h"
#include"echo_b.h"

void echo(int number)
{
    for(int i=1;i<number;i++)
    {
        printf("%s ",argv[i]);
    }
    printf("\n");
}