/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 10:40:07 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/14 19:35:04 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child(t_data *data, int *fd_pipe, char **envp)
{
	int	fd_outfile;

	fd_outfile = open(data->outfile, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd_outfile == -1)
	{
		free_child(data);
		perror("Open Outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_pipe[1]);
	if (data->path_cmd2 != NULL)
		execve(data->path_cmd2, data->cmd2, envp);
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(data->cmd2[0], 2);
	free_child(data);
	exit(127);
}

void	first_child(t_data *data, int *fd_pipe, char **envp)
{
	int	fd_infile;

	fd_infile = open(data->infile, O_RDONLY, 0444);
	if (fd_infile == -1)
	{
		free_child(data);
		perror("Open Infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	if (data->path_cmd1 != NULL)
		execve(data->path_cmd1, data->cmd1, envp);
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(data->cmd1[0], 2);
	free_child(data);
	exit(EXIT_SUCCESS);
}

void	parent(t_data data, char **envp)
{
	pid_t	pid_child1;
	pid_t	pid_child2;
	int		status;

	if (pipe(data.fd_pipe) == -1)
		exit_print_error(5, data);
	pid_child1 = fork();
	if (pid_child1 == -1)
		exit_print_error(4, data);
	if (pid_child1 == 0)
		first_child(&data, data.fd_pipe, envp);
	pid_child2 = fork();
	if (pid_child2 == -1)
		exit_print_error(4, data);
	if (pid_child2 == 0)
		second_child(&data, data.fd_pipe, envp);
	close(data.fd_pipe[0]);
	close(data.fd_pipe[1]);
	waitpid(pid_child2, &status, 0);
	wait(NULL);
	free_child(&data);
	exit(WEXITSTATUS(status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
	{
		ft_putendl_fd("\033[0;33m Correct Input:\033[0m", 2);
		ft_putendl_fd("\t./pipex infile cmd1 cmd2 outfile", 2);
		exit (EXIT_FAILURE);
	}
	ft_bzero(&data, sizeof(t_data));
	data.infile = argv[1];
	data.outfile = argv[4];
	data = create_command_path(argv, envp, data);
	parent(data, envp);
}
