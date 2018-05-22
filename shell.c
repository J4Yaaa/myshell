#include "shell.h"

int main()
{
    char msg[128];
    char* argv[128];
    char username[10];
    char hostname[10];
    char dirname[10];
    while(1)
    {
        get_username(username);
        get_hostname(hostname);
        get_dirname(dirname);
        //1.获取命令行
        printf("%s@%s %s >  ",username,hostname,dirname);
        scanf("%[^\n]%*c",msg);
        /* gets(msg); */
        //2.解析命令行
        int ret = do_parse(msg,argv);
        if(argv[0] == NULL)
        {
            getchar();
            continue;
        }
        //3.执行命令 
        //  a) 有 | 或者 >
        if(ret > 0)
        {
            if(Con == con_pipe)
            {//执行管道有关操作
                do_pipe(argv,ret);
            }
            else if(Con == con_direct)
            {//执行重定向有关操作
                do_direct(argv,ret);
            }
        }
        //  b) 没有管道或者重定向
        else
        {
            //  b.1)内建命令  ->  不建立新的进程
            if(strcmp("cd",argv[0]) == 0)
            {
                do_chdir(argv);
            }
            //  b.2)建立进程
            //      子进程替换
            //      父进程等待
            else
            {
                do_execute(argv);
            }
        }
    }
    return 0;
}
