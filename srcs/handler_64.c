/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:28:41 by dgalide           #+#    #+#             */
/*   Updated: 2018/03/20 19:00:52 by dgalide          ###   ########.fr       */
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
			print_addr(nm->value, 1);
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
	struct nlist_64 *array;
	t_nm			*lst;

	if (!security_func(buff, sym->stroff + sym->strsize))
		return (NULL);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	lst = NULL;
	i = -1;
	while (++i < (int)sym->nsyms)
		if (!(array[i].n_type & N_STAB))
			add_list_64(&lst, stringtable + array[i].n_un.n_strx, array[i]);
	return (lst);
}

static char	**get_sections(char **sections, struct segment_command_64 *segment)
{
	char				**tmp;
	int					i;
	struct section_64	*section;

	i = -1;
	if (segment->nsects < 1)
		return (sections);
	tmp = (char **)malloc(sizeof(char *) * (segment->nsects + 1));
	section = (struct section_64 *)(segment + 1);
	while (++i < (int)segment->nsects)
		(tmp[i] = format_section_name(section->sectname)) ? (section++) : 0;
	tmp[i] = 0;
	if (!sections)
		sections = ft_tab_cpy(tmp, sections);
	else
		sections = ft_tab_join(sections, tmp, 0, 0);
	return (sections);
}

int			handler_64(void *ptr, struct stat buff, char *name)
{
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char					**sections;

	sections = NULL;
	i = -1;
	if (!security_func(buff, sizeof(struct mach_header_64) * 2))
		return print_corrupted(name);
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	if (!security_func(buff, sizeof(struct mach_header_64) + header->sizeofcmds))
		return print_corrupted(name);
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			sym = (struct symtab_command *)lc;
		if (lc->cmd == LC_SEGMENT_64)
			sections = get_sections(sections, (struct segment_command_64 *)lc);
		lc = (void *)lc + lc->cmdsize;
	}
	if (!print_output(get_symbols(sym, ptr, buff), sections))
		return print_corrupted(name);
	return (1);
}
