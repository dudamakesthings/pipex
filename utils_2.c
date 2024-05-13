/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 18:35:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/13 18:47:08 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	create_command_path(char **argv, char **envp, t_data data)
{
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		ft_putendl_fd("permission denied", 2);
		exit(EXIT_SUCCESS);
	}
	if (argv[2][0] == ' ' && argv[2][1] == '\0')
		print_error(3, argv[2], data);
	if ((argv[3][0] == ' ' && argv[3][1] == '\0'))
		print_error(3, argv[3], data);
	data.cmd1 = ft_split(argv[2], ' ');
	data.path_cmd1 = check_path(data.cmd1[0], envp);
	if (data.path_cmd1 == NULL)
		print_error(2, argv[2], data);
	data.cmd2 = ft_split(argv[3], ' ');
	data.path_cmd2 = check_path(data.cmd2[0], envp);
	if (data.path_cmd2 == NULL)
		print_error(2, argv[3], data);
	return (data);
}

void	print_error(int flag, char *cmd, t_data data)
{
	if (flag == 2)
	{
		ft_putstr_fd("\033[0;31m Command not found: \033[0m", 2);
		ft_putendl_fd(cmd, 2);
	}
	if (flag == 3)
	{
		ft_putendl_fd("\033[0;31m Command not found\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	if (flag == 4)
	{
		perror("fork");
		free_child(&data);
		close_fd(data.fd_pipe);
		exit(EXIT_FAILURE);
	}
	if (flag == 5)
	{
		perror("pipe");
		free_child(&data);
		exit(EXIT_FAILURE);
	}
}

void	close_fd(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}
