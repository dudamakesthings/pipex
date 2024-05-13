/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 10:40:07 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/13 14:31:52 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child(char *outfile, char *path, char **cmd, int *fd_pipe, char **envp)
{
	int	fd_outfile;

	fd_outfile = open(outfile, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd_outfile == -1)
	{
		perror("Open Outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_pipe[1]);
	execve(path, cmd, envp);
	perror("Second Child execve");
	exit(127);
}

void	first_child(char *infile, char *path, char **cmd, int *fd_pipe, char **envp)
{
	int	fd_infile;

	fd_infile = open(infile, O_RDONLY, 0444);
	if (fd_infile == -1)
	{
		perror("Open Infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	execve(path, cmd, envp);
	perror("First Child execve");
	exit(127);
}

void	parent(char **cmd1, char *child1, char **cmd2, char *child2, char **envp, char **argv)
{
	int		fd_pipe[2];
	pid_t	pid_child1;
	pid_t	pid_child2;
	int		status;
	

	if (pipe(fd_pipe) == -1)
		print_error(5, NULL);
	pid_child1 = fork();
	if (pid_child1 == -1)
		print_error(4, NULL);
	if (pid_child1 == 0)
		first_child(argv[1], child1, cmd1, fd_pipe, envp);
	pid_child2 = fork();
	if (pid_child2 == -1)
		print_error(4, NULL);
	if (pid_child2 == 0)
		second_child(argv[4], child2, cmd2, fd_pipe, envp);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid_child2, &status, 0);
	waitpid(pid_child1, &status, 0);
	wait(NULL);
	free_child(cmd1, cmd2, child1, child2);
	exit(WEXITSTATUS(status));
}

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
	if (!envp)
		print_error(3, NULL);
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	child1 = check_path(cmd1[0], envp);
	if (child1 == NULL)
	{
		free_child(cmd1, cmd2, child1, NULL);
		print_error(2, cmd1);
	}
	child2 = check_path(cmd2[0], envp);
	if (child2 == NULL)
	{
		free_child(cmd2, cmd1, child1, child2);
		print_error(2, cmd2);
	}
	parent(cmd1, child1, cmd2, child2, envp, argv);
}
