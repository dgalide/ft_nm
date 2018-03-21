/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 17:31:01 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

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
		print_hex((otool->assembly)[i]);
	}
	ft_putstr(" \n");
	return (1);
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
	return (otool);
}

int		ft_otool(void *ptr, struct stat buff, char *name)
{
	int						magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		return (handler_64(ptr, buff, name));
	else if (magic == (int)MH_MAGIC)
		return (handler_32(ptr, buff, name));
	else if (magic == (int)FAT_CIGAM)
		return (get_fat_32(ptr, buff, name));
	else if (magic == (int)FAT_CIGAM_64)
		return (get_fat_64(ptr, buff, name));
	else
		return (-1);
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

int		main(int ac, char **av)
{
	int			i;

	if (ac < 2)
		return (put_error("Need at least one argument"));
	i = 0;
	while (++i < ac)
		otool_process(av[i]);
	return (0);
}
