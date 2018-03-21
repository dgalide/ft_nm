/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 15:45:25 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static	size_t	nbrlen(unsigned long long n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

void			print_letter(t_nm *nm, char **tab)
{
	char			type;
	char			*section_name;

	type = 0;
	type = ((nm->type & N_TYPE) == N_INDR) ? 'I' : type;
	type = (!type && (nm->type & N_TYPE) == N_STAB) ? '-' : type;
	type = (!type && (nm->type & N_TYPE) == N_UNDF
		&& (nm->type & N_EXT) && nm->value != 0) ? 'C' : type;
	type = (!type && (nm->type & N_TYPE) == N_UNDF
		&& (nm->type & N_TYPE) == N_PBUD) ? 'u' : type;
	type = (!type && (nm->type & N_TYPE) == N_UNDF) ? 'U' : type;
	type = (!type && (nm->type & N_TYPE) == N_ABS) ? 'A' : type;
	if (!type && (nm->type & N_TYPE) == N_SECT)
	{
		section_name = tab[nm->sect - 1];
		type = (section_name && (!ft_strcmp(section_name, "__text")
			|| !ft_strcmp(section_name, "__data")
			|| !ft_strcmp(section_name, "__bss"))) ?
		ft_toupper(section_name[2]) : 'S';
	}
	ft_putchar(' ');
	ft_putchar(!(nm->type & N_EXT) ? ft_tolower(type) : type);
	ft_putchar(' ');
	ft_putendl(nm->str);
}

void			print_addr(unsigned long long n, int boo)
{
	char				str[nbrlen(n) + 1];
	size_t				len;

	len = nbrlen(n) - 1;
	if (n == 0)
	{
		(boo) ? (ft_putstr("                ")) : ft_putstr("        ");
		return ;
	}
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (16 > 10 && n % 16 > 9) ?
			(n % 16) + ('a' - 10) : (n % 16) + 48;
		n /= 16;
		len--;
	}
	len = -1;
	if (boo)
		while (++len + ft_strlen(str) < 16)
			ft_putchar('0');
	else
		while (++len + ft_strlen(str) < 8)
			ft_putchar('0');
	ft_putstr(str);
}
