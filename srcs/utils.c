/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/20 15:20:47 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

char		*format_section_name(char *section_name)
{
	char	*output;
	// char	*ret;

	output = ft_memalloc(17);
	ft_strncpy(output, (char *)section_name, 16);
	// if ((ret = ft_strchr(output, ' ')) != NULL)
	// 	*ret = 0;
	return (output);
}

int					reverse_endianness(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}