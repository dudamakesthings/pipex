/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 10:40:07 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/08 17:56:41 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	ft_commands(char *str_cmd, char **envp)
// {
// 	char **cmd;
// 	char *path;

// 	if (str_cmd[0] == ' ' && str_cmd[1] == '\0')
// 	{
// 		ft_putendl_fd("\033[0;31m\033[1mInvalid Command\033[0m", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	cmd = ft_split(str_cmd, ' ');
// 	path = check_path(cmd[0], envp);
// 	execve(path, cmd, envp);
// }

// void	first_child(char **cmd1, int *fd_pipe, char **envp)
// {
// 	int	fd_infile;

// 	fd_infile = open(argv[1], O_RDONLY, 0444);
// 	if (fd_infile == -1)
// 	{
// 		perror("Open Infile");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd_infile, STDIN_FILENO);
// 	dup2(fd_pipe[1], STDOUT_FILENO);
// 	close(fd_pipe[0]);
// 	ft_commands(argv[2], envp);
// }

// void	parent(char **argv, int *fd_pipe, char **envp)
// {
// 	int	fd_outfile;

// 	fd_outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
// 	if (fd_outfile == -1)
// 	{
// 		perror("open outfile");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd_outfile, STDOUT_FILENO);
// 	dup2(fd_pipe[0], STDIN_FILENO);
// 	close(fd_pipe[1]);
// 	ft_commands(argv[3], envp);
// }

// void	pipex(char **cmd1, char *child1, char **cmd2, char *child2, char **envp)
// {
// 	int		fd_pipe[2];
// 	pid_t	pid_child1;
// 	pid_t	pid_child2;

// 	if (pipe(fd_pipe) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid_child1 = fork();
// 	if (pid_child1 == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	// if (pid_child1 == 0)
// 	// 	first_child(argv, fd_pipe, envp);
// }

int main(int argc, char *argv[], char *envp[])
{
	char	**cmd1;
	char	**cmd2;
	char	*child1;
	char	*child2;

	if (argc != 5)
	{
		ft_putendl_fd("\033[0;33m Correct Input:\033[0m", 2);
		ft_putendl_fd("\t./pipex infile cmd1 cmd2 outfile", 2);
		exit (EXIT_FAILURE);
	}
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	child1 = check_path(cmd1[0], envp);
	if (child1 == NULL)
		error_message_child(cmd1, cmd2, child1);
	child2 = check_path(cmd2[0], envp);
	if (child2 == NULL)
	{
		free(child2);
		error_message_child(cmd2, cmd1, child1);
	}
	// pipex
}
