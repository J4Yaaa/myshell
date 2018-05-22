#include "shell.h"

void get_username(char* username)
{
    //1.获取用户名
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    strcpy(username,pwd->pw_name);
}

void get_hostname(char* hostname)
{
    //2.获取主机名
    char name[10];
    gethostname(name,10);
    strcpy(hostname,name);
}

void get_dirname(char* dirname)
{
    //3.获取当前目录
    char buf[128];
    getcwd(buf,128); //获取当前目录的全路径
    //获取最后一个目录,即为当前目录
    char* dir[20] = {NULL};
    int i = 0;
    char* p = strtok(buf,"/");
    while(p != NULL)
    {
        dir[i++] = p;
        p = strtok(NULL,"/");
    }
    dir[i] = NULL;
    char* prev = dir[0];
    i = 1;
    while(dir[i] != NULL)
    {
        prev = dir[i];
        ++i;
    }
    strcpy(dirname,prev);
}
