#include "headers.h"
#include "ls_b.h"
#include "dirent.h"
#include "pwd.h"
#include "grp.h"
#include "time.h"
void perm(char *name)
{
    struct stat fileperms;
    struct passwd *user;
    struct group *grou;

    if (stat(name, &fileperms) == -1)
    {
        printf(":( Error while opening\n");
        return;
    }
    // file permission
    printf((S_ISDIR(fileperms.st_mode)) ? "d" : "-");
    printf((fileperms.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileperms.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileperms.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileperms.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileperms.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileperms.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileperms.st_mode & S_IROTH) ? "r" : "-");
    printf((fileperms.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileperms.st_mode & S_IXOTH) ? "x" : "-");
    // Number of links
    printf(" %ld ", fileperms.st_nlink);
    // User Name
    user = getpwuid(fileperms.st_uid);
    printf("%s\t", user->pw_name);
    // Group Name
    grou = getgrgid(fileperms.st_gid);
    printf("%s\t", grou->gr_name);
    // size in bytes
    printf("%zu\t", fileperms.st_size);
    // time
    char *timing = ctime(&fileperms.st_mtime);
    for (int i = 4; i <= 15; i++)
        printf("%c", timing[i]);
    // name
    //printf(" %s", fileperms.d);
}

long long total_l(char *name)
{
    long long int s = 0;
    struct dirent *de;
    DIR *dr = opendir(name);
    while ((de = readdir(dr)) != NULL)
    {
        if (de->d_name[0] != '.')
        {
            char info_path[1024];
            strcpy(info_path, name);
            if (name[strlen(name) - 1] != '/')
                strcat(info_path, "/");
            strcat(info_path, de->d_name);
            struct stat fileperms;
            stat(info_path, &fileperms);
            s += fileperms.st_blocks;
        }
    }
    closedir(dr);
    return s;
}
long long total_al(char *name)
{
    long long int s = 0;
    struct dirent *de;
    DIR *dr = opendir(name);
    while ((de = readdir(dr)) != NULL)
    {
        char info_path[1024];
        strcpy(info_path, name);
        if (name[strlen(name) - 1] != '/')
            strcat(info_path, "/");
        strcat(info_path, de->d_name);
        struct stat fileperms;
        stat(info_path, &fileperms);
        s += fileperms.st_blocks;
    }
    closedir(dr);
    return s;
}
int isafile(int i)
{
    struct stat fileperms;
    if (stat(argv[i], &fileperms) == -1)
    {
        return -1;
    }
    return ((S_ISDIR(fileperms.st_mode)) ? 0 : 1);
}
void ls(int start,int number)
{
    // flags check karte
    bool flag_a = false;
    bool flag_l = false;
    int count_flags = 0;
    for (int i = start; i < number; i++)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); j++)
            {
                if (argv[i][j] == 'a')
                {
                    flag_a = true;
                }
                else if (argv[i][j] == 'l')
                {
                    flag_l = true;
                }
            }
            count_flags++;
        }
    }
    // cases
    // 2^2=4 * 2(files/directory given or not)

    if (count_flags + 1 == number-start +1)
    {
        // extra kuch given nahi
        // 4 cases
        struct dirent *de;
        DIR *dr = opendir(".");
        if (dr == NULL)
        {
            printf("Could not open current directory");
            return;
        }
        if (!flag_a && !flag_l)
        {
            while ((de = readdir(dr)) != NULL)
            {
                if (de->d_name[0] != '.')
                {
                    printf("%s\n", de->d_name);
                }
            }
            printf("case 1 no flags no and no source given\n");
        }
        else if (!flag_a && flag_l)
        {
            printf("Total %lld\n", (total_l(".") / 2));
            while ((de = readdir(dr)) != NULL)
            {
                if (de->d_name[0] != '.')
                {
                    perm(de->d_name);
                    printf(" %s\n", de->d_name);
                }
            }
            printf("case 2 -l flag and no source given\n");
        }
        else if (flag_a && !flag_l)
        {
            while ((de = readdir(dr)) != NULL)
            {
                printf("%s\t", de->d_name);
            }
            printf("case 3 -a flag and no source given\n");
        }
        else
        {
            printf("Total %lld\n", (total_al(".") / 2));
            while ((de = readdir(dr)) != NULL)
            {
                perm(de->d_name);
                printf(" %s\n", de->d_name);
            }
            printf("case 4 -la flag and no source given\n");
        }
        closedir(dr);
    }
    else
    {
        if (!flag_a && !flag_l)
        {
            for (int i = start; i < number; i++)
            {
                if (argv[i][0] != '-')
                {
                    int type = isafile(i);
                    if (type == -1)
                    {
                        printf(":( Error while opening file\n");
                        continue;
                    }
                    else if (type == 0)
                    {
                        printf("%s:\n", argv[i]);
                        struct dirent *de;
                        DIR *dr = opendir(argv[i]);

                        while ((de = readdir(dr)) != NULL)
                        {
                            if (de->d_name[0] != '.')
                            {
                                printf("%s\n", de->d_name);
                            }
                        }
                    }
                    else
                    {
                        printf("%s\t", argv[i]);
                    }
                    printf("\n");
                }
            }
            printf("case 5 no flags but source given\n");
        }
        else if (!flag_a && flag_l)
        {
            for (int i = start; i < number; i++)
            {
                if (argv[i][0] != '-')
                {
                    int type = isafile(i);
                    if (type == -1)
                    {
                        printf(":( Error while opening %s\n", argv[i]);
                        continue;
                    }
                    else if (type == 0)
                    {
                        printf("%s:\n", argv[i]);
                        printf("Total %lld\n", (total_l(argv[i]) / 2));
                        struct dirent *de;
                        DIR *dr = opendir(argv[i]);
                        while ((de = readdir(dr)) != NULL)
                        {
                            if (de->d_name[0] != '.')
                            {
                                char info_path[1024];
                                strcpy(info_path, argv[i]);
                                if (argv[i][strlen(argv[i]) - 1] != '/')
                                    strcat(info_path, "/");
                                strcat(info_path, de->d_name);
                                perm(info_path);
                                printf(" %s\n", de->d_name);
                            }
                        }
                        closedir(dr);
                    }
                    else
                    {
                        perm(argv[i]);
                        printf(" %s\n", argv[i]);
                    }
                    printf("\n");
                }
            }
            printf("case 6 -l flags but source given\n");
        }
        else if (flag_a && !flag_l)
        {
            for (int i = start; i < number; i++)
            {
                if (argv[i][0] != '-')
                {
                    int type = isafile(i);
                    if (type == -1)
                    {
                        printf(":( Error while opening %s\n", argv[i]);
                        continue;
                    }
                    else if (type == 0)
                    {
                        printf("%s:\n", argv[i]);
                        struct dirent *de;
                        DIR *dr = opendir(argv[i]);
                        while ((de = readdir(dr)) != NULL)
                        {
                            printf(" %s\n", de->d_name);
                        }
                        closedir(dr);
                    }
                    else
                    {
                        printf("%s\n", argv[i]);
                    }
                    printf("\n");
                }
            }
            printf("case 7 -a flags but source given\n");
        }
        else
        {
            for (int i = start; i < number; i++)
            {
                if (argv[i][0] != '-')
                {
                    int type = isafile(i);
                    if (type == -1)
                    {
                        printf(":( Error while opening %s\n", argv[i]);
                        continue;
                    }
                    else if (type == 0)
                    {
                        printf("%s:\n", argv[i]);
                        printf("Total %lld\n", (total_al(argv[i]) / 2));
                        struct dirent *de;
                        DIR *dr = opendir(argv[i]);
                        while ((de = readdir(dr)) != NULL)
                        {
                            char info_path[1024];
                            strcpy(info_path, argv[i]);
                            if (argv[i][strlen(argv[i]) - 1] != '/')
                                strcat(info_path, "/");
                            strcat(info_path, de->d_name);
                            perm(info_path);
                            printf(" %s\n", de->d_name);
                        }
                        closedir(dr);
                    }
                    else
                    {
                        perm(argv[i]);
                        printf(" %s\n", argv[i]);
                    }
                    printf("\n");
                }
            }
            printf("case 8 -al flags but source given\n");
        }
    }
}