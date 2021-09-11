#include"headers.h"
#include"pwd.h"

void pwd(int number)
{
    if(number!=1)
    {
        printf("Error!! some wrong number of commands given for pwd");
    }
    else{
        getcwd(curr_dir,sizeof(curr_dir));
        printf("%s\n",curr_dir);
    }
}