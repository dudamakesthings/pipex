/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 18:35:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/14 19:25:31 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	create_command_path(char **argv, char **envp, t_data data)
{
	data.cmd1 = ft_split(argv[2], ' ');
	if (data.cmd1[0] == NULL)
		exit_print_error(3, data);
	if (access(argv[2], F_OK | X_OK) == 0)
		data.path_cmd1 = ft_strdup(argv[2]);
	else
		data.path_cmd1 = check_path(data.cmd1, envp);
	data.cmd2 = ft_split(argv[3], ' ');
	if (data.cmd2[0] == NULL)
		exit_print_error(3, data);
	if (access(argv[3], F_OK | X_OK) == 0)
		data.path_cmd2 = ft_strdup(argv[3]);
	else
		data.path_cmd2 = check_path(data.cmd2, envp);
	return (data);
}

void	exit_print_error(int flag, t_data data)
{
	if (flag == 3)
	{
		free_child(&data);
		ft_putendl_fd("\033[0;31mPermission denied\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	if (flag == 4)
	{
		perror("fork");
		free_child(&data);
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		exit(EXIT_FAILURE);
	}
	if (flag == 5)
	{
		perror("pipe");
		free_child(&data);
		exit(EXIT_FAILURE);
	}
}
