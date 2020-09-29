/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:50:20 by ldevelle          #+#    #+#             */
/*   Updated: 2020/09/29 17:41:26 by ezalos           ###   ########.fr       */
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
	if (IS_FILE_DIR(sys->statbuf))
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

static t_rbt			*file_routine(t_sys_files *daddy, t_rbt *node,
							struct dirent *file_infos)
{
	t_sys_files		*file;

	if (parse_get("all") || file_infos->d_name[0] != '.')
	{
		file = file_struct(file_infos->d_name, daddy);
		if (parse_get("time"))
			node = tree_insert_func(node, file, &sort_files_time);
		else
			node = tree_insert_func(node, file, &sort_files_alpha);
	}
	return (node);
}

t_rbt					*list_files(t_sys_files *daddy)
{
	t_rbt			*node;
	DIR				*directory_infos;
	struct dirent	*file_infos;

	node = NULL;
	directory_infos = NULL;
	directory_infos = opendir(daddy->path);
	if (directory_infos)
	{
		file_infos = readdir(directory_infos);
		if (file_infos)
			while (file_infos)
			{
				node = file_routine(daddy, node, file_infos);
				file_infos = readdir(directory_infos);
			}
		else
			perror(ERROR_DIR_READ);
		if (closedir(directory_infos) != 0)
			perror(ERROR_DIR_CLOSE);
	}
	else
		perror(ERROR_DIR_OPEN);
	return (node);
}
