#include "main.h"

/**
 * main - a simple shell to run commands
 * @argc: argument count unused.
 * @argv: argument values unused.
 * @envp: environment for shell.
 * Return: 0 on success, -1 on error.
 */
int main(int argc, char *argv[], char *envp[])
{
	char *buffer, *exec, *delim, *args[1024];
	size_t len;
	ssize_t read;
	pid_t child;
	int status, count;

	(void)argc;
	(void)argv;
	buffer = NULL;
	len = 0;
	delim = " \n\r";

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("%s$ ", getenv("PWD"));
		read = getline(&buffer, &len, stdin);
		if (read == EOF)
		{
			printf("\n");
			break;
		}
		count = 0;
		args[count] = strtok(buffer, delim);
		while (args[count] && count < 1023)
			args[++count] = strtok(NULL, delim);
		args[++count] = NULL;

		if (strcmp(args[0], "exit") == 0)
			exit_shell();
		if (strcmp(args[0], "env") == 0)
		{
			for (count = 0; envp[count] != NULL; count++)
				printf("%s\n", envp[count]);
			continue;
		}
		exec = resolve_realpath(args[0]);
		if (exec == NULL)
		{
			printf("Error updating PATH\n");
			continue;
		}
		child = fork();
		if (child == -1)
		{
			perror("Error:");
			free(buffer);
			return (-1);
		}
		if (child == 0)
		{
			if (execve(exec, args, NULL) == -1)
			{
				perror("Error:");
				free(buffer);
				free(exec);
				return (-1);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(buffer);
	free(exec);
	return (0);
}
