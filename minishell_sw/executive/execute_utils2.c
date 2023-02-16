#include "execute.h"

static char	**make_path_split(void)
{
	char	**result;
	char	*path;

	path = find_env_val("PATH");
	if (path == NULL)
		return (NULL);
	result = ft_split(path, ':');
	if (result == NULL)
		exit(MALLOC_FAILURE);
	free(path);
	return (result);
}

static char	*strjoin_slash(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	if (tmp == NULL)
		exit(MALLOC_FAILURE);
	tmp = ft_strjoin_and_free(tmp, s2);
	if (tmp == NULL)
		exit(MALLOC_FAILURE);
	return (tmp);
}

void	find_path(char **cmd)
{
	char	**path_split;
	char	*merged_path;

	path_split = make_path_split();
	while (*path_split)
	{
		merged_path = strjoin_slash(*path_split, cmd[0]);
		if (access(merged_path, F_OK) == SUCCESS)
		{
			free(cmd[0]);
			cmd[0] = merged_path;
			merged_path = NULL;
			if (access(cmd[0], X_OK) == SUCCESS)
				return ;
		}
		free(merged_path);
		++path_split;
	}
}

void	access_check(char *cmd, char mode)
{
	if (access(cmd, F_OK) == FAILURE)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		if (mode == '/')
			perror_msg(cmd, 127);
		else
		{
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": ", 2);
			error_msg(COMMAND_NOT_FOUND, 127);
		}
	}
	else if (access(cmd, X_OK) == FAILURE)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		perror_msg(cmd, 126);
	}
}
