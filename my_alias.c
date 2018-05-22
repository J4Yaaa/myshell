#include "shell.h"

int my_alias(char* p,char* str)
{
    size_t size = sizeof(alias_arr)/sizeof(alias_arr[0]);
    size_t i = 0;
    for(; i < size; ++i)
    {
        if(strcmp(p,alias_arr[i]) == 0)
        {
            size_t len = strlen(replace_alias_arr[i]);
            memcpy(str,replace_alias_arr[i],len);
            str[len] = '\0';
            return 1;
        }
    }
    return 0;
}

