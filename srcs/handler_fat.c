/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 17:44:07 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static int		launch(void *ptr, int offset, struct stat buff, char *name)
{
	if (!security_func(buff, offset))
		return (print_corrupted(name));
	return (ft_nm((void *)ptr + offset, buff, name));
}

int				get_fat_32(void *ptr, struct stat buff, char *name)
{
	int					i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					narch;

	i = -1;
	if (!security_func(buff, sizeof(struct fat_header) * 2))
		return (print_corrupted(name));
	header = (struct fat_header *)ptr;
	arch = (struct fat_arch *)((void *)ptr + sizeof(struct fat_header));
	narch = (reverse_endianness(header->nfat_arch));
	if (!security_func(buff, sizeof(struct fat_arch) * narch))
		return (print_corrupted(name));
	while (++i < (int)narch)
	{
		if (reverse_endianness(arch->cputype) == CPU_TYPE_X86_64 ||
		reverse_endianness(arch->cputype) == CPU_TYPE_X86)
			return (launch(ptr, reverse_endianness(arch->offset), buff, name));
		arch++;
	}
	return (1);
}

int				get_fat_64(void *ptr, struct stat buff, char *name)
{
	int					i;
	struct fat_header	*header;
	struct fat_arch_64	*arch;
	int					narch;

	i = -1;
	if (!security_func(buff, sizeof(struct fat_header) * 2))
		return (print_corrupted(name));
	header = (struct fat_header *)((void *)ptr);
	arch = (struct fat_arch_64 *)((void *)ptr + sizeof(struct fat_header));
	narch = reverse_endianness(header->nfat_arch);
	if (!security_func(buff, sizeof(struct fat_arch_64) * narch))
		return (print_corrupted(name));
	while (++i < (int)narch)
	{
		if (reverse_endianness(arch->cputype) == CPU_TYPE_X86_64 ||
		reverse_endianness(arch->cputype) == CPU_TYPE_X86)
			return (launch(ptr, reverse_endianness(arch->offset), buff, name));
		arch++;
	}
	return (1);
}
