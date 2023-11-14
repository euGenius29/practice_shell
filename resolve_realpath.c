#include "main.h"
/**
 * resolve_realpath - resolves to the real path set in env
 * @command: command from the command line
 * Return: 0 on success, -1 on error
 */
char *resolve_realpath(char *command)
{
	char *token, *env_path, *path_copy, *fullpath;

	env_path = getenv("PATH");
	path_copy = strdup(env_path);
	if (!path_copy)
	{
		fprintf(stderr, "Error: Path environment variable not set.\n");
		return (NULL);
	}
	token = strtok(path_copy, ":");
	while (token)
	{
		fullpath = malloc(strlen(token) + strlen(command) + 2);
		if (!fullpath)
		{
			perror("Error:");
			free(path_copy);
			return (NULL);
		}
		token += 4;
		sprintf(fullpath, "%s/%s", token, command);
		if (access(fullpath, X_OK) == 0)
		{
			if (setenv("PATH", fullpath, 0) == -1)
			{
				perror("Error:");
				free(fullpath);
				free(path_copy);
				return (NULL);
			}
			free(path_copy);
			return (fullpath);
		}
		free(fullpath);
		token = strtok(NULL, ":");
	}
	printf("%s: command not found\n", command);
	free(path_copy);
	return (NULL);
}
