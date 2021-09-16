#include"headers.h"
#include"pwd_b.h"

void pwd(int start,int number)
{
    if((number-start)!=1)
    {
        printf("Error!! some wrong number of commands given for pwd");
    }
    else{
        getcwd(curr_dir,sizeof(curr_dir));
        printf("%s\n",curr_dir);
    }
}