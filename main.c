/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 10:40:07 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/07 18:35:41 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_commands(char *str_cmd, char **envp)
{
	char **cmd;
	char *path;

	if (str_cmd[0] == ' ' && str_cmd[1] == '\0')
	{
		ft_putendl_fd("\033[0;31m\033[1mInvalid Command\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	cmd = ft_split(str_cmd, ' ');
	path = check_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("\033[0;31mCommand not found: \033[0m", 2);
		ft_putendl_fd(cmd[0], 2);
		free_split(cmd);
		exit(127);
	}
}

void child(char **argv, int *fd_pipe, char **envp)
{
	int	fd_infile;

	fd_infile = open(argv[1], O_RDONLY, 444);
	if (fd_infile == -1)
	{
		perror("Open Infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_infile, 0);
	dup2(fd_pipe[1], 1);
	close(fd_pipe[0]);
	ft_commands(argv[2], envp);
}

void	parent(char **argv, int *fd_pipe, char **envp)
{
	int	fd_outfile;

	fd_outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 666);
	if (fd_outfile == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_outfile, 1);
	dup2(fd_pipe[0], 0);
	close(fd_pipe[1]);
	ft_commands(argv[3], envp);
}

int main(int argc, char *argv[], char *envp[])
{
	int		fd_pipe[2];
	pid_t	pid;
	// char *argv1[] = {"ls", "-la", NULL};

	// execve("/usr/bin/ls", argv1, envp);

	if (argc != 5)
	{
		ft_putendl_fd("\033[0;33m Correct Input:\033[0m", 2);
		ft_putendl_fd("\t./pipex infile cmd1 cmd2 outfile", 2);
		exit (EXIT_FAILURE);
	}
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (!pid)
		child(argv, fd_pipe, envp);
	parent(argv, fd_pipe, envp);
}
