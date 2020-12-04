/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:36:43 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/05 10:09:14 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int ft_count_words(char *str)
{
	int i;
	int count;
	int word;

	i = 0;
	count = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i + 1] == '\0')
		{
			if (word == 1)
			{
				word = 0;
				count++;
			}
		}
		else if (str[i] > 32)
			word = 1;
		i++;
	}
	return (count);
}

static int ft_strlen_sp(int index, char *str)
{
	int i;

	i = index;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		i++;
	}
	return (i - index);
}

char **ft_split_whitespaces(char *str)
{
	char **tab;
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = 0;
	len = ft_count_words(str);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		tab[j] = (char *)malloc(sizeof(char) * (ft_strlen_sp(i, str) + 1));
		k = 0;
		while (!(str[i] == '\0' || str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[len] = 0;
	return (tab);
}
