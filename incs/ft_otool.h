/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 17:36:09 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct			s_otool
{
	struct stat			buff;
	unsigned char		*assembly;
	int					size;
	int					offset;
	int					error;
	void				*ptr;
	unsigned long long	addr;
}						t_otool;

int						main(int ac, char **av);
int						ft_otool(void *ptr, struct stat buff, char *name);
t_otool					*otool_init(struct stat buff, void *ptr);

int						handler_64(void *ptr, struct stat buff, char *name);
int						handler_32(void *ptr, struct stat buff, char *name);
int						get_fat_32(void *ptr, struct stat buff, char *name);
int						get_fat_64(void *ptr, struct stat buff, char *name);

int						security_func(struct stat buff, int offset);
int						reverse_endianness(int x);

int						print_output(t_otool *otool, int archbool, char *name);
void					print_addr(unsigned long long n, int boo);
void					print_hex(unsigned char byte);
int						print_corrupted(char *name);
int						put_error(char *error);

#endif
