/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/20 12:16:11 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static void		push_list_next(t_nm *tmp, t_nm *new)
{
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new;
			break ;
		}
		if (ft_strcmp(tmp->next->str, new->str) > 0)
		{
			new->next = tmp->next;
			tmp->next = new;
			break ;
		}
		if (ft_strcmp(tmp->next->str, new->str) == 0)
		{
			if (tmp->next->value > new->value)
			{
				new->next = tmp->next;
				tmp->next = new;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

static void		push_list(t_nm **lt, t_nm *tmp, t_nm *new)
{
	if (ft_strcmp(tmp->str, new->str) > 0)
	{
		new->next = tmp;
		*lt = new;
		return ;
	}
	if (ft_strcmp(tmp->str, new->str) == 0)
	{
		if (tmp->value > new->value)
		{
			new->next = tmp;
			*lt = new;
			return ;
		}
	}
	push_list_next(tmp, new);
}

void			add_list_64(t_nm **nm, char *str, struct nlist_64 array)
{
	t_nm *new;
	t_nm *tmp;

	tmp = *nm;
	new = (t_nm*)malloc(sizeof(t_nm));
	new->value = array.n_value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = str;
	new->next = NULL;
	if (!*nm)
		*nm = new;
	else
		push_list(nm, tmp, new);
}

void			add_list_32(t_nm **nm, char *str, struct nlist array)
{
	t_nm *new;
	t_nm *tmp;

	tmp = *nm;
	new = (t_nm*)malloc(sizeof(t_nm));
	new->value = array.n_value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = str;
	new->next = NULL;
	if (!*nm)
		*nm = new;
	else
		push_list(nm, tmp, new);
}