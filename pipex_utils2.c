/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:35:40 by mac               #+#    #+#             */
/*   Updated: 2022/02/21 17:06:22 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_checker(char *cmd, char **env)
{
	char	**all_paths;
	char	*path;
	char	*part_of_path;
	int		i;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK))
			perror("Permission denied: ");
	}
	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		part_of_path = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(part_of_path, cmd);
		free(part_of_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*s;
	size_t	neelen;

	i = 0;
	s = (char *)haystack;
	neelen = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (s[i] != '\0' && i + neelen <= len)
	{
		if (ft_strncmp(haystack, needle, neelen) == 0)
			return ((char *)haystack);
		i++;
		haystack++;
	}
	return (NULL);
}

int	count_words(const char *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (c)
	{
		while (s[i])
		{
			if (s[i] != c)
				res++;
			while (s[i] != c && s[i])
				i++;
			while (s[i] == c)
				i++;
		}
	}
	else
		res = 0;
	return (res);
}

int	words_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
		{
			tab[i] = ft_substr(s, 0, words_len(s, c));
			s = s + words_len(s, c);
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}