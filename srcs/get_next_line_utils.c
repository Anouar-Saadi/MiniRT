/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 14:42:28 by asaadi            #+#    #+#             */
/*   Updated: 2019/12/28 14:46:30 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

char			*ft_strchr(const char *s, int c)
{
	char	*str;
	char	r;
	int		i;

	r = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == r)
			return (str + i);
		i++;
	}
	return (0);
}

char			*ft_strdup(const char *s1)
{
	char	*cpy;
	int		len;
	int		i;

	len = ft_strlen(s1);
	if (!(cpy = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = start;
	j = 0;
	if (i < len)
		while (j < len && s[i])
			sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*pre;
	char	*suf;
	char	*res;
	int		i;
	int		j;

	pre = (char *)s1;
	suf = (char *)s2;
	if (!suf || !pre)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(pre) + ft_strlen(suf) + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (pre[++i])
		res[i] = pre[i];
	while (suf[j])
		res[i++] = suf[j++];
	res[i] = '\0';
	return (res);
}
