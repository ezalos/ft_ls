/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:19:42 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 11:20:43 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		print_ls(t_rbt *node)
{
	t_sys_files *file = node->content;

	if (parse_get("recursive"))
		if (file->check == IS_CURRENT_DIR || file->check == IS_UP_DIR)
			return (0);
	print_file_color(file->statbuf, file->path);
	print_file_name(file->d_name);
	ft_printf("%~{}");
	ft_printf("  ");
	return (0);
}

int		print_ls_l(t_rbt *node)
{
	t_sys_files *file = node->content;

	if (parse_get("recursive"))
		if (file->check == IS_CURRENT_DIR || file->check == IS_UP_DIR)
			return (0);
	print_file_color(file->statbuf, file->path);
	print_file_type(file->statbuf);
	ft_printf("%~{}");
	print_file_mode(file->statbuf, file);
	print_file_link_count(file->statbuf);
	print_file_ownership(file->statbuf);
	print_file_size(file->statbuf.st_size, TRUE);
	ft_printf(" ");
	print_file_last_modif(file->statbuf);
	print_file_color(file->statbuf, file->path);
	print_file_name(file->d_name);
	ft_printf("%~{}");
	print_file_link(file);
	ft_printf("\n");
	return (0);
}

void	ls_output(t_rbt *node)
{
	t_sys_files	*file;

	file = node->content;
	if (parse_get("recursive"))
		if (file->parent)
		{
			if (file->parent->parent)
				ft_printf("\n");
			if (OS_IS_LINUX)
				ft_printf("%s:\n", file->parent->path);
			else if (!OS_IS_LINUX && file->parent->parent)
				ft_printf("%s:\n", file->parent->path);
		}

	if (parse_get("list"))//TODO: if more than one file
	{
		if (file->parent)
			get_format(&file->parent->format, 0);
		print_folder_size(node);
		if (!parse_get("reverse"))
			tree_inorder(node, &print_ls_l);
		else
			tree_inrorder(node, &print_ls_l);
	}
	else
	{
		if (!parse_get("reverse"))
			tree_inorder(node, &print_ls);
		else
			tree_inrorder(node, &print_ls);
		ft_printf("\n");
	}
}
