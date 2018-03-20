/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/20 15:51:02 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

void	ft_nm(void *ptr, struct stat buff)
{
	int						magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		handler_64(ptr, buff);
	else if (magic == (int)MH_MAGIC)
		handler_32(ptr, buff);
	else if (magic == (int)FAT_CIGAM)
		get_fat_32(ptr, buff);
	else if (magic == (int)FAT_CIGAM_64)
		get_fat_64(ptr, buff);
}

int		put_error(char *error)
{
	ft_putendl_fd(error, 2);
	return (-1);
}

int		main(int ac, char **av)
{
	int			fd;
	struct stat buff;
	void		*ptr;

	fd = 0;
	ptr = NULL;
	if (ac != 2)
		return (put_error("Error, only one argument needed"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (put_error("Open Failed"));
	if (fstat(fd, &buff) < 0)
		return (put_error("Fstat error"));
	if ((ptr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
														== MAP_FAILED)
		return (put_error("Mmap error"));
	ft_nm(ptr, buff);
	close(fd);
	munmap(ptr, buff.st_size);
	return (0);
}
