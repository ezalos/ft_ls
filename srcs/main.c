/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/09/23 19:33:21 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		sort_files_alpha(void *one, void *two)
{
	char	*name_one;
	char	*name_two;

	name_one = ((t_sys_files*)one)->name_lowercase;
	name_two = ((t_sys_files*)two)->name_lowercase;
#if __linux__ 
	if (*name_one == '.')
		name_one++;
	if (*name_two == '.')
		name_two++;
	if (((t_sys_files*)one)->check == IS_UP_DIR)
	{
		name_one++;
		if (((t_sys_files*)two)->check == IS_CURRENT_DIR)
			return (1);
	}
	if (((t_sys_files*)two)->check == IS_UP_DIR)
	{
		name_two++;
		if (((t_sys_files*)one)->check == IS_CURRENT_DIR)
			return (-1);
	}
#endif
	return (ft_strcmp(name_one, name_two));
}

int		sort_files_time(void *one, void *two)
{
	long long	time_one;
	long long	time_two;

	time_one = ((t_sys_files*)one)->statbuf.st_mtime;
	time_two = ((t_sys_files*)two)->statbuf.st_mtime;

	if (time_one < time_two)
		return (1);
	else if (time_one == time_two)
		return (sort_files_alpha(one, two));
	return (-1);
}

int		recursive(t_rbt *node)
{
	t_sys_files		*file;
	int				ret = 0;

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
		if (parse_get("Recurse"))
			tree_inorder(node, &recursive);
		//free all
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_sys_files	*file = NULL;

	parse_new("ls", PROGRAME_DESCRIPTION);

	parse_add_option('R', "Recurse",	"Recursively visit each directory");
	parse_add_option('r', "reverse",	"Reverse sort order");
	parse_add_option('l', "list",		"List file information");
	parse_add_option('a', "all",		"Show hidden files");
	parse_add_option('t', "time",		"Sort files by time");
	parse_add_option('h', "help",		"Display Usage (this message)");

	parse_add_arg("PATH", "List information about the content of the directory.\
			Default is current directory");

	if (parse_args(ac, av) == FAILURE)
		return (0);

	if (parse_get("help") != NULL)
		return (parse_usage());
	if (parse_get("PATH") != NULL)
		file = file_struct(parse_get("PATH")->raw[0], NULL);
	else
		file = file_struct(DEFAULT_ARGUMENT, NULL);
	if (file)
		one_level(file);
	return (0);
}
