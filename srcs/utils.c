/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/20 19:05:15 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

char		*format_section_name(char *section_name)
{
	char	*output;

	output = ft_memalloc(17);
	ft_strncpy(output, (char *)section_name, 16);
	return (output);
}

int			reverse_endianness(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

int			security_func(struct stat buff, int offset)
{
	if (offset > buff.st_size)
		return (0);
	return (1);
}

int			print_corrupted(char *name)
{
	ft_putstr_fd("File ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(" is corrupted.", 2);
	return (0);
}