#include "headers.h"
#include "pinfo.h"

void pinfo(int number)
{
    int pid;
    if(number==1)
    {
        pid=(int)getpid();
    }
    else if(number == 2)
    {
        pid=atoi(argv[1]);
    }
    else
    {
        printf(":( Incorrect Number of arguments\n");
        return;
    }
    printf("pid = %d\n",pid);
    // pid pta hai
    // process state
    // memory
    // exe path
    /*
        process state 3rd line
        memory 23rd line           
        ye dono to /proc/pid/stat se nikal lunga

    */
    char path1[1024];
    char path2[1024];
    sprintf(path1,"/proc/%d/stat",pid);
    sprintf(path2,"/proc/%d/exe",pid);
    int ravi_shastri; // opener :)
    ravi_shastri=open(path1,O_RDONLY);
    if(ravi_shastri==-1)
    {
        perror(":( file not found\n");
        return;
    }
    else
    {
        char *buff = (char *)calloc(512,sizeof(char));
        read(ravi_shastri, buff, 512);
        char* process_state;
        char* virtual_memory;
        char* majboori;
        majboori = strtok(buff, " ");
        int position=0;
        while(majboori != NULL && position<24)
        {
            position++;
            if(position==3)
            {
                process_state=majboori;
            }
            else if(position==23)
            {
                virtual_memory=majboori;
            }
            majboori=strtok(NULL, " ");
        }
        printf("Process state = %s\n",process_state);
        printf("Virtual Memory = %s\n",virtual_memory);
    }
}