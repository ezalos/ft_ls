/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:47:22 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/01 21:33:49 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int			recursive(t_rbt *node)
{
	t_sys_files		*file;
	int				ret;

	ret = 0;
	file = node->content;
	if (file && (file->check == IS_DIR))
		ret = one_level(file);
	return (ret);
}

void		free_memory(t_sys_files *unix_file, t_rbt *node, int8_t to_free)
{
	if (node && !(unix_file->empty_folder_case && unix_file->parent))
		tree_free(node, free_file_struct);
	else if (node)
	{
		ft_memdel((void**)&node);
		node = (void*)1;
	}
	if (!node || to_free)
		free_file_struct((void**)&unix_file);
}

int8_t		file_data_creation(t_sys_files *unix_file, t_rbt **node)
{
	int8_t			to_free;

	to_free = 0;
	if (IS_FILE_DIR(unix_file->statbuf))
	{
		*node = list_files(unix_file);
		if (!*node && unix_file->check != IS_CURRENT_DIR
		&& unix_file->open_denied == FALSE)
			unix_file->empty_folder_case = 1;
		else if (!unix_file->parent)
			to_free = 1;
	}
	if ((!*node && unix_file->empty_folder_case
	&& unix_file->open_denied == FALSE)
	|| (unix_file->parent == NULL && !IS_FILE_DIR(unix_file->statbuf)))
	{
		unix_file->lonely_file = !IS_FILE_DIR(unix_file->statbuf) ? 1 : 0;
		if (parse_get("time"))
			*node = tree_insert_func(*node, unix_file, &sort_files_time);
		else
			*node = tree_insert_func(*node, unix_file, &sort_files_alpha);
	}
	else if (!IS_FILE_DIR(unix_file->statbuf))
		to_free = -1;
	return (to_free);
}

int			one_level(t_sys_files *unix_file)
{
	t_rbt			*node;
	int8_t			to_free;

	node = NULL;
	if ((to_free = file_data_creation(unix_file, &node)) == -1)
		return (0);
	if (node && unix_file->open_denied == FALSE)
	{
		ls_output(node);
		if (parse_get("recursive") && !unix_file->empty_folder_case)
			tree_inorder(node, &recursive);
	}
	free_memory(unix_file, node, to_free);
	return (1);
}
