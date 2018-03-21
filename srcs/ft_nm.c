/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 18:20:40 by dgalide          ###   ########.fr       */
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

static void	nm_process(char *av, int ac)
{
	int			fd;
	struct stat buff;
	void		*ptr;

	fd = 0;
	ptr = NULL;
	if ((fd = open(av, O_RDONLY)) < 0)
		put_error("Open Failed");
	if (fstat(fd, &buff) < 0)
		put_error("Fstat error");
	if ((ptr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
														== MAP_FAILED)
		put_error("Mmap error");
	if (ac > 2)
		ft_printf("\n%s:\n", av);
	ft_nm(ptr, buff, av);
	close(fd);
	munmap(ptr, buff.st_size);
}

int			ft_nm(void *ptr, struct stat buff, char *name)
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

int			main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 2)
		return (put_error("Need at least one argument"));
	while (++i < ac)
		nm_process(av[i], ac);
	return (0);
}
