/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/04/10 19:57:27 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

static int	get_assembly(t_otool *otool)
{
	unsigned char	*tmp;
	unsigned char	*output;
	int				i;

	if (otool->error)
		return (0);
	if ((output = (unsigned char *)malloc(sizeof(unsigned char)
		* (otool->size + 1))) == NULL)
		return (0);
	i = -1;
	tmp = (unsigned char *)(otool->ptr);
	while (++i < otool->size)
		output[i] = (unsigned char)(tmp[(otool->offset) + i]);
	output[i] = 0;
	otool->assembly = output;
	return (otool->size);
}

static int	get_section(struct segment_command_64 *segment, t_otool *otool)
{
	struct section_64	*section;
	int					i;

	if (segment->nsects < 1)
		return (0);
	section = (struct section_64 *)(segment + 1);
	i = -1;
	while (++i < (int)segment->nsects)
	{
		if (!ft_strcmp(section->sectname, "__text") &&
			!ft_strcmp(section->segname, "__TEXT"))
		{
			if (!security_func(otool->buff, section->offset + section->size))
				otool->error = 1;
			otool->addr = section->addr;
			otool->size = section->size;
			otool->offset = section->offset;
			return (get_assembly(otool));
		}
	}
	return (0);
}

int			handler_64(void *ptr, struct stat buff, char *name)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						i;
	t_otool					*otool;

	otool = otool_init(buff, ptr);
	if (!security_func(buff, sizeof(struct mach_header_64 *)))
		return (1);
	header = (struct mach_header_64 *)ptr;
	if (!security_func(buff, sizeof(*header) + header->sizeofcmds))
		return (1);
	lc = (struct load_command *)(header + 1);
	i = -1;
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (get_section((struct segment_command_64 *)lc, otool))
				break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (print_output(otool, 1, name));
}
