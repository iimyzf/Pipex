/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:33:55 by mac               #+#    #+#             */
/*   Updated: 2022/02/17 13:33:05 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	s1len;
	size_t	i;
	char	*str;

	i = 0;
	s1len = ft_strlen(s1);
	str = (char *) malloc(sizeof(char) * s1len + 1);
	if (!str)
		return (NULL);
	while (s1[i] && i < s1len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	char	*joined;

	if (!s1)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	joined = (char *) malloc(sizeof(char) * (s1len + s2len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i < s1len + s2len)
	{
		joined[i] = s2[i - s1len];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*str;
	size_t	i;
	size_t	slen;

	str = (char *) s;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len > slen)
		len = slen;
	sub = (char *) malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (str[start] && i < len)
	{
		sub[i++] = str[start++];
	}
	sub[i] = '\0';
	return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	i = 0;
	if (n != 0)
	{
		if (c1[0] == '\0' || c2[0] == '\0')
			return (c1[0] - c2[0]);
		while (i < n && (c1[i] || c2[i]))
		{
			if (c1[i] != c2[i])
				return (c1[i] - c2[i]);
			else
				i++;
		}
	}
	return (0);
}