/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:47:22 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 09:47:26 by ezalos           ###   ########.fr       */
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
	t_rbt			*node = NULL;

	if (IS_FILE_DIR(unix_file->statbuf))//	IS DIR
		node = list_files(unix_file);
	else if (unix_file->parent == NULL)//	lonely file
	{
		if (parse_get("time"))
			node = tree_insert_func(node, unix_file, &sort_files_time);
		else
			node = tree_insert_func(node, unix_file, &sort_files_alpha);
	}
	else
		return (0);
	if (node)
	{
		ls_output(node);
		if (parse_get("recursive"))
			tree_inorder(node, &recursive);
		//TODO: free all
	}
	return (1);
}
