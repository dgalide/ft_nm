#include "../incs/ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>

void	print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	void			*stringtable;
	struct nlist_64 *array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		ft_printf("%-30s\ttype : %x\tvalue : %x\tndesc: %x\n", stringtable + array[i].n_un.n_strx, stringtable + array[i].n_type, stringtable + array[i].n_value, stringtable + array[i].n_desc);
		i += 1;
	}
}


char	**get_sections64(char **sections, struct segment_command_64 *lc)
{
	// char		**tmp;
	int			i;
	(void)lc;
	i = ft_strlen(*sections);

	ft_printf("nb sections : %d\n", i);
	return NULL;
}

void	ft_nm(void *ptr, struct stat buff)
{
	int						magic;
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char					**sections;

	magic = *(int *)ptr;
	i = 0;
	if (magic == (int)MH_MAGIC_64)
	{
		header = (struct mach_header_64 *)ptr;
		ncmds = header->ncmds;
		lc = (void *)ptr + sizeof(struct mach_header_64);
		while (i++ < ncmds)
		{
			if (lc->cmd == LC_SYMTAB)
			{
				sym = (struct symtab_command *)lc;
				print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			}
			else if (lc->cmd == LC_SEGMENT_64)
				sections = get_sections64(sections, (struct segment_command_64)lc);
			lc = (void *) lc + lc->cmdsize;
		}
		
	}
	(void)buff;
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
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return put_error("Open Failed");
	if (fstat(fd, &buff) < 0)
		return put_error("Fstat error");
	if ((ptr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return put_error("Mmap error");
	ft_nm(ptr, buff);
	return (0);
}