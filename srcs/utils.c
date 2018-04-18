/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/04/18 14:52:42 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"
#include <stdio.h>

int			put_error(char *error)
{
	ft_putendl_fd(error, 2);
	return (1);
}

int			reverse_endianness(uintmax_t y)
{
	uintmax_t		x;

	x = y;
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

int			security_func(struct stat buff, uintmax_t offset)
{
	if (offset > (uintmax_t)buff.st_size)
		return (0);
	return (1);
}

int			print_corrupted(char *name)
{
	ft_putstr_fd("File ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(" is corrupted.", 2);
	return (1);
}

void		print_hex(unsigned char byte)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
}
