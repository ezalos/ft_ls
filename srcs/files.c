/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:50:20 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/03 13:44:03 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int8_t					is_file_dir(struct stat sb)
{
	return (S_IFDIR == (sb.st_mode & S_IFMT) ? TRUE : FALSE);
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
	if ((directory_infos = opendir(daddy->path)) != NULL)
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
	{
		ft_printf("\n%s:\n", daddy->path);
		perror(ERROR_DIR_OPEN);
		daddy->open_denied = TRUE;
	}
	return (node);
}
