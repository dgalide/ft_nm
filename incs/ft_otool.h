#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "../libft/includes/libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach/machine.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

typedef struct 			s_otool
{
	struct stat			buff;
	unsigned char		*assembly;
	int					size;
	int					offset;
	int					error;
	void				*ptr;
	unsigned long long	addr;
}						t_otool;

int			main(int ac, char **av);
int			put_error(char *error);
int			security_func(struct stat buff, int offset);
int			print_corrupted(char *name);
void		print_addr(unsigned long long n, int boo);

#endif