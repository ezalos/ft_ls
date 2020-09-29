/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:47:22 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 16:23:05 by ezalos           ###   ########.fr       */
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

	// ft_printf("ONELVL sys_file %p\n", unix_file);
	if (IS_FILE_DIR(unix_file->statbuf))
	{
		// ft_printf("%s\n", unix_file->d_name);
		node = list_files(unix_file);
		if ((!node && (unix_file->check != IS_CURRENT_DIR)))
		{
			unix_file->empty_folder_case = 1;
			// ft_printf("XXXXX %s\n", unix_file->d_name);

		}
		// ft_printf("ONELVL node %p\n", node);
	}
	if ((!node && unix_file->empty_folder_case)
	|| (unix_file->parent == NULL && !IS_FILE_DIR(unix_file->statbuf)))
	{
		// ft_printf("ONELVL Heyy %s\n", unix_file->d_name);
		if (parse_get("time"))
			node = tree_insert_func(node, unix_file, &sort_files_time);
		else
			node = tree_insert_func(node, unix_file, &sort_files_alpha);
	}
	else if (!IS_FILE_DIR(unix_file->statbuf))
		return (0);
	// ft_printf("ONELVL help %p\n", node);
	if (node)
	{
		ls_output(node);
		if (parse_get("recursive") && !unix_file->empty_folder_case)
			tree_inorder(node, &recursive);
		//TODO: free all
	}
	return (1);
}
