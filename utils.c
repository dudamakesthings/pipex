/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 11:25:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/13 14:28:14 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path(char *str_cmd, char **envp)
{
	int		i;
	char	*execute;
	char	**path;
	char	*part_path;

	i = 0;
	path = ft_split(ft_find_path(envp), ':');
	while (path[i])
	{
		part_path = ft_strjoin(path[i], "/");
		execute = ft_strjoin(part_path, str_cmd);
		free(part_path);
		if (access(execute, F_OK | X_OK) == 0)
			return (free_split(path), execute);
		free(execute);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_child(char **cmd, char **cmd2, char *chd1, char *chd2)
{
	free_split(cmd);
	free_split(cmd2);
	if (chd2)
		free(chd2);
	free(chd1);
}

void	print_error(int flag, char **cmd)
{
	if (flag == 2)
	{
		ft_putstr_fd("\033[0;31m Command not found: \033[0m", 2);
		ft_putendl_fd(cmd[0], 2);
		exit(127);
	}
	if (flag == 3)
	{
		ft_putendl_fd("\tUnexpected error", 2);
		exit (EXIT_FAILURE);
	}
	if (flag == 4)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (flag == 5)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
