/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 10:40:20 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/14 17:56:28 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
	char	*infile;
	char	*outfile;
	int		fd_pipe[2];

}	t_data;

t_data	create_command_path(char **argv, char **envp, t_data data);
void	free_split(char **array);
char	*ft_find_path(char **envp);
char	*check_path(char **str_cmd, char **envp);
void	free_child(t_data *data);
void	exit_print_error(int flag, t_data data);

#endif