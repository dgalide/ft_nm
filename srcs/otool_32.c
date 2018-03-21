/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/21 17:26:04 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_otool.h"

static int 		get_assembly(t_otool *otool)
{
	unsigned char	*tmp;
	unsigned char 	*output;
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

static int		get_section(struct segment_command *segment, t_otool *otool)
{
	struct section 		*section;
	int					i;

	if (segment->nsects < 1)
		return (0);
	section = (struct section *)(segment + 1);
	i = -1;
	while (++i < (int)segment->nsects)
	{
		if (!ft_strcmp(section->sectname, "__text") && !ft_strcmp(section->segname, "__TEXT"))
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

int				handler_32(void *ptr, struct stat buff, char *name)
{
	struct mach_header		*header;
	struct load_command		*lc;
	int						i;
	t_otool					*otool;

	otool = otool_init(buff, ptr);
	if (!security_func(buff, sizeof(struct mach_header *)))
		return (0);
	header = (struct mach_header *)ptr;
	if (!security_func(buff, sizeof(*header) + header->sizeofcmds))
		return (0);
	lc = (struct load_command *)(header + 1);
	i = -1;
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			if (get_section((struct segment_command *)lc , otool))
				break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (print_output(otool, 0, name));
}