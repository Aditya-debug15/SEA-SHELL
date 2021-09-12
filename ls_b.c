#include "headers.h"
#include "ls_b.h"

void perm()
{
    
}
void ls(int number)
{
    // flags check karte
    bool flag_a=false;
    bool flag_l=false;
    for(int i=1;i<number;i++)
    {
        if(argv[i][0]=='-')
        {
            for(int j=1;j<strlen(argv[i]);j++)
            {
                if(argv[i][j]=='a')
                {
                    flag_a=true;
                }
                else if(argv[i][j]=='l')
                {
                    flag_l=true;
                }
            }
        }
    }
    // cases
    // 2^2=4
    if(!flag_a && !flag_l)
    {
        for(int i=1;i<number;i++)
        {
            if(argv[i][0]!='-')
            {
                
            }
        }
    }
}