#include "shell.h"

//进行普通的进程替换
void do_execute(char* argv[])
{
    pid_t pid = fork();
    if(pid  < 0)
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0) //child
    {
        execvp(argv[0],argv);
        perror(argv[0]);
        /* printf("======%d======\n", __LINE__); */
        exit(1);
    }
    else
    {
        while(wait(NULL) != pid);
    }
}

//管道间的进程替换
void do_pipe(char* argv[],int ret)
{
    int fd[2];
    if(pipe(fd) < 0)
    {
        perror("pipe");
    }
    argv[ret] = NULL;
    pid_t pid1 = fork(); //brother
    if(pid1 < 0)
    {
        perror("fork 1");
        exit(1);
    }
    else if(pid1 == 0) //child1
    {
        dup2(fd[1],1);
        execvp(argv[0],argv);
        perror(argv[0]);
        /* printf("======%d======\n", __LINE__); */
        exit(1);
    }
    else //father
    {
        pid_t pid2 = fork();
        if(pid2 < 0)
        {
            perror("fork 2");
            exit(1);
        }
        else if(pid2 == 0) //child
        {
            dup2(fd[0],0);
            execvp(argv[ret+1],argv+ret+1);
            perror(argv[ret+1]);
            /* printf("======%d======\n", __LINE__); */
            exit(1);
        }
        /* wait(NULL); */
        wait(NULL);
    }
}

//重定向
void do_direct(char* argv[],int ret)
{
    const char* str = argv[ret+1];
    int fd = open(str,O_RDWR|O_CREAT,0644);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    argv[ret] = NULL;
    pid_t pid1 = fork();
    if(pid1 < 0)
    {
        perror("fork 1");
        exit(1);
    }
    else if(pid1 == 0) //child 1
    {
        dup2(fd,1);
        execvp(argv[0],argv);
        perror(argv[0]);
        /* printf("======%d======\n", __LINE__); */
        exit(1);
    }
    else //parent
    {
        pid_t pid2 = fork();
        if(pid2 < 0)
        {
            perror("fork 2");
            exit(1);
        }
        else if(pid2 == 0) //child 2
        {
            dup2(fd,0);
            /* printf("======%d======%s\n", __LINE__,argv[ret+1]); */
            exit(1);
        }
        close(fd);
        wait(NULL);
    }
}

//内建命令cd不执行替换,执行chdir
void do_chdir(char* argv[])
{
    int i = 1;
    while(argv[i] != NULL)
    {
        chdir(argv[i]);
        ++i;
    }
}
