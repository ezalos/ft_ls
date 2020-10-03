/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:12:40 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/03 16:18:50 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int				fill_name(t_sys_files *sys, char *name, char *path)
{
	char			*tmp;
	int				i;

	sys->d_name = ft_strdup(name);
	if (path)
	{
		if (*path && path[ft_strlen(path) - 1] != '/')
		{
			tmp = ft_strdup("/");
			sys->path = ft_strjoin(path, tmp);
			ft_strdel(&tmp);
			tmp = sys->path;
			sys->path = ft_strjoin(tmp, sys->d_name);
			ft_strdel(&tmp);
		}
		else
			sys->path = ft_strjoin(path, sys->d_name);
	}
	else
		sys->path = ft_strdup(sys->d_name);
	sys->name_lowercase = ft_strdup(sys->d_name);
	i = -1;
	while (sys->name_lowercase[++i])
		sys->name_lowercase[i] = ft_tolower(sys->name_lowercase[i]);
	return (SUCCESS);
}

static int				file_check(t_sys_files *sys, char *name)
{
	if (is_file_dir(sys->statbuf))
	{
		if ((!ft_strncmp(name, UP_DIR, UP_DIR_LEN)
					&& name[UP_DIR_LEN] == '\0'))
			return (IS_UP_DIR);
		else if ((!ft_strncmp(name, CURRENT_DIR, CURRENT_DIR_LEN)
					&& name[CURRENT_DIR_LEN] == '\0'))
			return (IS_CURRENT_DIR);
		else
			return (IS_DIR);
	}
	else
		return (IS_FILE);
}

t_sys_files				*file_struct(char *name, t_sys_files *parent)
{
	t_sys_files			*sys;

	sys = ft_memalloc(sizeof(t_sys_files));
	sys->parent = parent;
	if (parent)
		fill_name(sys, name, parent->path);
	else
		fill_name(sys, name, NULL);
	if (lstat(sys->path, &sys->statbuf) != 0)
	{
		ft_printf("ERROR: %s\n", sys->d_name);
		perror(ERROR_DIR_STAT);
		return (NULL);
	}
	sys->check = file_check(sys, name);
	if (parent)
		update_format(sys, &parent->format);
	return (sys);
}

void					free_file_struct(void **content)
{
	t_sys_files			*file;

	file = *content;
	if (file)
	{
		ft_memdel((void**)&file->d_name);
		ft_memdel((void**)&file->path);
		ft_memdel((void**)&file->name_lowercase);
		ft_memdel((void**)&file->path);
		ft_memdel((void**)content);
	}
}
