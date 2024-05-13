/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 10:40:20 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/13 13:06:19 by edribeir      ########   odam.nl         */
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
#include <sys/wait.h>

void	free_split(char **array);
char	*ft_find_path(char **envp);
char	*check_path(char *str_cmd, char **envp);
void	free_child(char **cmd, char **cmd2, char *chd1, char *chd2);
void	print_error(int flag, char **cmd);

#endif