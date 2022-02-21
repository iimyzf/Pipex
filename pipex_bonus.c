/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:03:01 by mac               #+#    #+#             */
/*   Updated: 2022/02/21 18:24:23 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **env)
{
	char	**cmd;
	char	*path;
	int 	i;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = path_checker(cmd[0], env);
	if (!path)	
	{
		// while (cmd[++i])
		// 	free(cmd[i]);
		// free(cmd);
		error();
	}
	if (execve(path, cmd, env) == -1)
		error();
}

void	process(char *argv, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO); //dup2 copies the content of its arg 2 to its arg 1!
		execute(argv, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		i = 2;
		filein = open(argv[1], O_RDONLY);
		fileout = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
		dup2(filein, STDIN_FILENO);
		while (i < argc - 2)
			process(argv[i++], env);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], env);
	}
	else
        error();
}