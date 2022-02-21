/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:34:07 by mac               #+#    #+#             */
/*   Updated: 2022/02/21 18:19:20 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	child_process(char **argv, char **env, int *fd)
{
	int		input;
	char	**cmd;

	input = open(argv[1], O_RDONLY);
	if (input < 0)
		error();
	dup2(fd[1], STDOUT_FILENO);
	if (dup2(input, STDIN_FILENO) < 0)
		error();
	close(fd[0]);
	close(fd[1]);
	close(input);
	cmd = ft_split(argv[2], ' ');
	execve(path_checker(cmd[0], env), cmd, NULL);
}

void	child2_process(char **argv, char **env, int *fd)
{
	int		output;
	char	**cmd;

	output = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (output < 0)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(output);
	cmd = ft_split(argv[3], ' ');
	execve(path_checker(cmd[0], env), cmd, NULL);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (argc == 5)
	{
		pipe(fd);
		pid = fork();
		if (pid < 0)
			error();
		if (pid == 0)
			child_process(argv, env, fd);
		pid2 = fork();
		if (pid2 < 0)
			error();
		if (pid2 == 0)
			child2_process(argv, env, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		error();
}