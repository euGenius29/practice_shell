#include "main.h"

/**
 * command_check - checks if command exists
 *
 * @command: command to be checked
 *
 * Return: 1 if yes, 0 if no
 */
int command_check(const char *command)
{
	return (access(command, X_OK) == 0);
}

/**
 * exit_shell - exits the shell in interactive mode
 *
 * Return: void
 */
void exit_shell(void)
{
	printf("%s\n\n[Disconnected...]\n", "exit");
	exit(0);
}

/**
 * _printenv - prints enviornment variables
 *
 * Return: void
 */
void _printenv(void)
{
	char **envp;

	envp = environ;
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
