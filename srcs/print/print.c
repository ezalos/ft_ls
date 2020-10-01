/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:19:42 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/01 21:17:04 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		print_ls(t_rbt *node)
{
	t_sys_files *file;

	file = node->content;
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
	t_sys_files *file;

	file = node->content;
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

void	ls_print_path(t_rbt *node)
{
	t_sys_files	*file;

	file = node->content;
	if (parse_get("recursive")
	|| (parse_get("PATH")->arg_place < parse_mem()->ac - 1))
	{
		if (file->parent)
		{
			if (file->parent->parent || file->empty_folder_case)
				ft_printf("\n");
			if (file->empty_folder_case)
				ft_printf("%s:\n", file->path);
			else if (OS_IS_LINUX)
				ft_printf("%s:\n", file->parent->path);
			else if (!OS_IS_LINUX && file->parent->parent)
				ft_printf("%s:\n", file->parent->path);
		}
		else if (file->empty_folder_case)
			ft_printf("%s:\n", file->path);
	}
}

void	ls_output_list(t_rbt *node)
{
	t_sys_files	*file;

	file = node->content;
	if (file->parent)
		get_format(&file->parent->format, 0);
	if (!file->lonely_file || (file->empty_folder_case && OS_IS_LINUX))
		print_folder_size(node);
	if (!file->empty_folder_case)
	{
		if (!parse_get("reverse"))
			tree_inorder(node, &print_ls_l);
		else
			tree_inrorder(node, &print_ls_l);
	}
	get_format(NULL, -1);
}

void	ls_output(t_rbt *node)
{
	t_sys_files	*file;

	file = node->content;
	ls_print_path(node);
	if (parse_get("list"))
		ls_output_list(node);
	else
	{
		if (!file->empty_folder_case)
		{
			if (!parse_get("reverse"))
				tree_inorder(node, &print_ls);
			else
				tree_inrorder(node, &print_ls);
		}
		ft_printf("\n");
	}
}
