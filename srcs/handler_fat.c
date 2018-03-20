/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/20 15:06:42 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

void		get_fat_32(void *ptr, struct stat buff)
{
	int					i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					narch;

	i = -1;
	header = (struct fat_header *)ptr;
	arch = (struct fat_arch *)((void *)ptr + sizeof(struct fat_header));
	narch = reverse_endianness(header->nfat_arch);
	while (++i < (int)narch)
	{
		if (reverse_endianness(arch->cputype) == CPU_TYPE_X86_64 ||
		reverse_endianness(arch->cputype) == CPU_TYPE_X86)
		{
			ft_nm((void *)ptr + reverse_endianness(arch->offset), buff);
			return ;
		}
		arch++;
	}
}

void		get_fat_64(void *ptr, struct stat buff)
{
	int					i;
	struct fat_header	*header;
	struct fat_arch_64	*arch;
	int					narch;

	i = -1;
	header = (struct fat_header *)((void *)ptr);
	arch = (struct fat_arch_64 *)((void *)ptr + sizeof(struct fat_header));
	narch = reverse_endianness(header->nfat_arch);
	while (++i < (int)narch)
	{
		if (reverse_endianness(arch->cputype) == CPU_TYPE_X86_64 ||
		reverse_endianness(arch->cputype) == CPU_TYPE_X86)
		{
			ft_nm((void *)ptr + reverse_endianness(arch->offset), buff);
			return ;
		}
		arch++;
	}
}