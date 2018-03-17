#include "../incs/ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>

int	ft_nm(void *ptr, struct stat buff)
{
	(void)ptr;
	(void)buff;
	return 1;
}

int put_error(char *error)
{
	ft_putendl(error);
	return -1;
}

int main(int ac, char **av) 
{
	int 		fd;
	struct stat buff;
	void		*ptr;

	fd = 0;
	ptr = NULL;
	if (ac != 2)
		return put_error("Error, only one argument needed");
	if ((fd = open(av[1], O_RDONLY) < 0))
		return put_error("Open Failed");
	if (fstat(fd, &buff) < 0)
		return put_error("Fstat error");
	if ((ptr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return put_error("Mmap error");
	ft_nm(ptr, buff);
	return (0);
}