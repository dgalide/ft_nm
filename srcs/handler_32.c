/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/04/10 19:38:38 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_nm.h"

static int	print_output(t_nm *nm, char **sections)
{
	t_nm *tmp;

	if (!nm)
		return (0);
	while (nm)
	{
		if (nm->value == 0 && (nm->type & N_TYPE) != N_UNDF)
			ft_putstr("0000000000000000");
		else
			print_addr(nm->value, 0);
		print_letter(nm, sections);
		tmp = nm->next;
		free(nm);
		nm = tmp;
	}
	return (1);
}

static t_nm	*get_symbols(struct symtab_command *sym, void *ptr,
	struct stat buff)
{
	int				i;
	void			*stringtable;
	struct nlist	*array;
	t_nm			*lst;

	if (!security_func(buff, sym->stroff + sym->strsize))
		return (NULL);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	lst = NULL;
	i = -1;
	while (++i < (int)sym->nsyms)
		if (!(array[i].n_type & N_STAB))
			add_list_32(&lst, stringtable + array[i].n_un.n_strx, array[i]);
	return (lst);
}

static int	get_sections(char ***sections,
	struct segment_command *segment, struct stat buff)
{
	char				**tmp;
	int					i;
	struct section		*section;

	i = -1;
	if (segment->nsects < 1)
		return (1);
	if (!security_func(buff, segment->fileoff))
		return (0);
	tmp = (char **)malloc(sizeof(char *) * (segment->nsects + 1));
	section = (struct section *)(segment + 1);
	while (++i < (int)segment->nsects)
		(tmp[i] = format_section_name(section->sectname)) ? (section++) : 0;
	tmp[i] = 0;
	if (!(*sections))
		*sections = ft_tab_cpy(tmp, *sections);
	else
		*sections = ft_tab_join(*sections, tmp, 0, 0);
	return (1);
}

int			handler_32(void *ptr, struct stat buff, char *name)
{
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char					**sections;

	sections = NULL;
	sym = NULL;
	i = -1;
	if (!security_func(buff, sizeof(struct mach_header) * 2))
		return (print_corrupted(name));
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header);
	if (!security_func(buff, sizeof(*header) + header->sizeofcmds))
		return (print_corrupted(name));
	while (++i < (int)header->ncmds)
	{
		(lc->cmd == LC_SYMTAB) ? sym = (struct symtab_command *)lc : 0;
		if (lc->cmd == LC_SEGMENT)
			if (!get_sections(&sections, (struct segment_command *)lc, buff))
				return (print_corrupted(name));
		lc = (void *)lc + lc->cmdsize;
	}
	return (!print_output(get_symbols(sym, ptr, buff), sections)) ?
	(print_corrupted(name)) : 0;
}
