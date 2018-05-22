#include "shell.h"

int do_parse(char* input,char* output[])
{
    if(input == NULL || output == NULL)
    {
        return -1;
    }
    int output_size = 0;
    char* p = strtok(input," ");
    while(p != NULL)
    {
        output[output_size++] = p;
        p = strtok(NULL," ");
    }
    output[output_size] = NULL;
    int i = 0;
    for(;output[i] != NULL; ++i)
    {
        if(strcmp(output[i],"|") == 0)
        {//有管道
            Con = con_pipe;
            return i;
        }
        if(strcmp(output[i],">") == 0)
        {//有重定向符
            Con = con_direct;
            return i;
        }
    }
    return 0;
}
