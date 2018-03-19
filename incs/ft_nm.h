#ifndef FT_NM_H
# define FT_NM_H

# include "../libft/includes/libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

typedef struct			s_nm
{
	unsigned long long	value;
	char				*str;
	uint8_t				type;
	uint8_t				sect;
	struct s_nm			*next;
}						t_nm;				

int 			main(int ac, char **av);
void			handler_64(void *ptr, struct stat buff);
void			add_list_64(t_nm **lt, char *str, struct nlist_64 array);

void			print_letter(t_nm *nm, char **tab);
void			print_addr(unsigned long long n, int boo);

char			*format_section_name(char *section_name);

#endif