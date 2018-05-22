#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include <string.h>
#include <fcntl.h>

enum Contain
{
    con_pipe,
    con_direct
};

enum Contain Con;

static const char* alias_arr[] = {"ll","cl","rm"};
static const char* replace_alias_arr[] = {"ls -l","clear","rm -i"};

int do_parse(char* input,char* output[]);
void do_execute(char* argv[]);
void get_username(char* username);
void get_hostname(char* hostname);
void get_dirname(char* dirname);
void do_chdir(char* argv[]);
void do_pipe(char* argv[],int ret);
void do_direct(char* argv[],int ret);
