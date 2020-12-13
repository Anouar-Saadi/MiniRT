/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:28:05 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 13:02:25 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ft_add_lights(t_light **alst, t_light *new)
{
	if (!*alst)
	{
		*alst = new;
	}
	else if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void			ft_add_objects(t_objects **alst, t_objects *new)
{
	if (!*alst)
	{
		*alst = new;
	}
	else if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

static t_camera	*ft_lstlast_camera(t_camera *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void			ft_add_cameras(t_camera **alst, t_camera *new)
{
	t_camera *temp;

	if (*alst)
	{
		temp = ft_lstlast_camera(*alst);
		temp->next = new;
		new->next = NULL;
		new->previous = temp;
	}
	else
		*alst = new;
}
