#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>


extern char **environ;




int command_check(const char *command);
void exit_shell();
void _printenv();
int perror_buf();

#endif

