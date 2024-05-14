/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 11:25:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/14 19:52:49 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path(char **cmd, char **envp)
{
	int		i;
	char	*execute;
	char	**path;
	char	*part_path;

	i = 0;
	path = ft_split(ft_find_path(envp), ':');
	if (path == NULL)
	{
		ft_putendl_fd("\033[0;33m\tNot ENV, Unexpected error\033[0m", 2);
		exit (EXIT_FAILURE);
	}
	while (path[i])
	{
		part_path = ft_strjoin(path[i], "/");
		execute = ft_strjoin(part_path, cmd[0]);
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

void	free_child(t_data *data)
{
	if (data->cmd1 != 0)
		free_split(data->cmd1);
	if (data->cmd2 != 0)
		free_split(data->cmd2);
	if (data->path_cmd2 != 0)
		free(data->path_cmd2);
	if (data->path_cmd1 != 0)
		free(data->path_cmd1);
}
