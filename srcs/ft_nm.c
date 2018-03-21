/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 14:56:49 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

char	*format_section_name(char *section_name)
{
	char	*output;

	output = ft_memalloc(17);
	ft_strncpy(output, (char *)section_name, 16);
	return (output);
}

int		ft_nm(void *ptr, struct stat buff, char *name)
{
	int						magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		handler_64(ptr, buff, name);
	else if (magic == (int)MH_MAGIC)
		handler_32(ptr, buff, name);
	else if (magic == (int)FAT_CIGAM)
		get_fat_32(ptr, buff, name);
	else if (magic == (int)FAT_CIGAM_64)
		get_fat_64(ptr, buff, name);
	return (1);
}

int		main(int ac, char **av)
{
	int			fd;
	struct stat buff;
	void		*ptr;

	fd = 0;
	ptr = NULL;
	if (ac != 2)
		return (put_error("Error, argument needed"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (put_error("Open Failed"));
	if (fstat(fd, &buff) < 0)
		return (put_error("Fstat error"));
	if ((ptr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
														== MAP_FAILED)
		return (put_error("Mmap error"));
	ft_nm(ptr, buff, av[1]);
	close(fd);
	munmap(ptr, buff.st_size);
	return (0);
}
