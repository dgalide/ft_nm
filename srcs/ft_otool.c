/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 16:25:08 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"
#include <stdio.h>

void	print_byte_to_hex(unsigned char byte)
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

int		print_output(t_otool *otool, int archbool, char *name)
{
	int		i;

	if (otool->error)
		return (print_corrupted(name));
	i = -1;
	ft_printf("%s:\nContents of (__TEXT,__text) section\n", name);
	print_addr(((otool->addr)), archbool);
	ft_putchar('\t');
	while (++i < otool->size)
	{
		if (!(i % 16) && i != 0)
		{
			ft_putstr(" \n");
			print_addr(((otool->addr) + i), archbool);
			ft_putchar('\t');
		}
		else if ((i % 16) && i != 0)
			ft_putchar(' ');
		print_byte_to_hex((otool->assembly)[i]);
	}
	ft_putstr(" \n");
	return (1);
}

int 	get_assembly(t_otool *otool)
{
	unsigned char	*tmp;
	unsigned char 	*output;
	int				i;

	if (otool->error)
		return (0);
	if ((output = (unsigned char *)malloc(sizeof(unsigned char) * (otool->size + 1))) == NULL)
		return (0);
	i = -1;
	tmp = (unsigned char *)(otool->ptr);
	while (++i < otool->size)
		output[i] = (unsigned char)(tmp[(otool->offset) + i]);
	output[i] = 0;
	otool->assembly = output;
	return otool->size;
}

int		get_section(struct segment_command_64 *segment, t_otool *otool)
{
	struct section_64 	*section;
	int					i;

	if (segment->nsects < 1 || ft_strcmp(segment->segname, "__TEXT") != 0)
		return (0);
	section = (struct section_64 *)(segment + 1);
	i = -1;
	while (++i < (int)segment->nsects)
	{
		if (!ft_strcmp(section->sectname, "__text"))
		{
			if (!security_func(otool->buff, section->offset + section->size))
				otool->error = 1;
			otool->addr = section->addr;
			otool->size = section->size;
			otool->offset = section->offset;
			return (get_assembly(otool));
		}
	}
	return (0);
}

t_otool	*otool_init(struct stat buff, void *ptr)
{
	t_otool *otool;

	otool = (t_otool *)malloc(sizeof(t_otool));
	otool->buff = buff;
	otool->offset = 0;
	otool->error = 0;
	otool->assembly = NULL;
	otool->ptr = ptr;
	return otool;
}

int		handler_64(void *ptr, struct stat buff, char *name)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						i;
	t_otool					*otool;

	otool = otool_init(buff, ptr);
	if (!security_func(buff, sizeof(struct mach_header_64 *)))
		return (0);
	header = (struct mach_header_64 *)ptr;
	if (!security_func(buff, sizeof(*header) + header->sizeofcmds))
		return (0);
	lc = (struct load_command *)(header + 1);
	i = -1;
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (get_section((struct segment_command_64 *)lc , otool))
				break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (print_output(otool, 1, name));
}

int		ft_otool(void *ptr, struct stat buff, char *name)
{
	int						magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		return (handler_64(ptr, buff, name));
	else
		return (-1);
	// else if (magic == (int)MH_MAGIC)
	// 	return (handler_32(ptr, buff));
	// else if (magic == (int)FAT_CIGAM)
	// 	return (get_fat_32(ptr, buff));
	// else if (magic == (int)FAT_CIGAM_64)
	// 	return (get_fat_64(ptr, buff));
}

int		otool_process(char *av)
{
	int			fd;
	struct stat buff;
	void		*ptr;

	fd = 0;
	ptr = NULL;
	if ((fd = open(av, O_RDONLY)) < 0)
		return (put_error("Open Failed"));
	if (fstat(fd, &buff) < 0)
		return (put_error("Fstat error"));
	if ((ptr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
														== MAP_FAILED)
		return (put_error("Mmap error"));
	if (ft_otool(ptr, buff, av) <= 0)
		return (print_corrupted(av));
	close(fd);
	munmap(ptr, buff.st_size);
	return (0);
}

int				main(int ac, char **av)
{
	int			i;

	if (ac < 2)
		return (put_error("Need at least one argument"));
	i = 0;
	while (++i < ac)
		otool_process(av[i]);
	return (0);
}