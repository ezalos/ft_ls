/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:47:22 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/30 13:12:27 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		recursive(t_rbt *node)
{
	t_sys_files		*file;
	int				ret;

	ret = 0;
	file = node->content;
	if (file && (file->check == IS_DIR))
		ret = one_level(file);
	return (ret);
}

int		one_level(t_sys_files *unix_file)
{
	t_rbt			*node;

	node = NULL;
	if (IS_FILE_DIR(unix_file->statbuf))
	{
		node = list_files(unix_file);
		if ((!node && (unix_file->check != IS_CURRENT_DIR)))
			unix_file->empty_folder_case = 1;
	}
	if ((!node && unix_file->empty_folder_case)
	|| (unix_file->parent == NULL && !IS_FILE_DIR(unix_file->statbuf)))
	{
		if (parse_get("time"))
			node = tree_insert_func(node, unix_file, &sort_files_time);
		else
			node = tree_insert_func(node, unix_file, &sort_files_alpha);
	}
	else if (!IS_FILE_DIR(unix_file->statbuf))
		return (0);
	if (node)
	{
		ls_output(node);
		if (parse_get("recursive") && !unix_file->empty_folder_case)
			tree_inorder(node, &recursive);
		if (!unix_file->empty_folder_case)
			tree_free(node, free_file_struct);
		else
			ft_memdel((void**)&node);
	}
	return (1);
}
