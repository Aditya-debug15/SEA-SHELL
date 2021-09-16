#include"headers.h"
#include"echo_b.h"

void echo(int start,int number)
{
    for(int i=start;i<number;i++)
    {
        printf("%s ",argv[i]);
    }
    printf("\n");
}