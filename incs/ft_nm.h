/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:24:05 by dgalide           #+#    #+#             */
/*   Updated: 2018/04/18 14:53:14 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../libft/includes/libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach/machine.h>
# include <mach-o/fat.h>
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

int						main(int ac, char **av);
int						ft_nm(void *ptr, struct stat buff, char *name);

int						handler_64(void *ptr, struct stat buff, char *name);
int						handler_32(void *ptr, struct stat buff, char *name);

int						get_fat_64(void *ptr, struct stat buff, char *name);
int						get_fat_32(void *ptr, struct stat buff, char *name);

void					add_list_64(t_nm **lt,
								char *str, struct nlist_64 array);
void					add_list_32(t_nm **nm, char *str, struct nlist array);

void					print_letter(t_nm *nm, char **tab);
void					print_addr(unsigned long long n, int boo);

char					*format_section_name(char *section_name);
int						reverse_endianness(uintmax_t x);
int						security_func(struct stat buff, uintmax_t offset);
int						print_corrupted(char *name);
int						put_error(char *error);

#endif
