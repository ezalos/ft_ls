/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/06/01 00:03:25 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		sort_files(void *one, void *two)
{
	char	*name_one;
	char	*name_two;
	int		res = 0;

	name_one = ((t_sys_files*)one)->name_lowercase;
	name_two = ((t_sys_files*)two)->name_lowercase;
	if (*name_one == '.')
		name_one++;
	if (*name_two == '.')
		name_two++;
	res = ft_strcmp(name_one, name_two);

	return (res);
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

	if (S_IFDIR == (unix_file->statbuf.st_mode & S_IFMT)) // IS DIR
		node = list_files(unix_file);
	else if (unix_file->parent != NULL)
		return (0);
	else
		node = tree_insert_func(node, unix_file, &sort_files);
	if (node)
	{
		ls_output(node);
		if (parse_get("Recurse"))
			tree_inorder(node, &recursive);
		//free all
	}
	return (1);
}

# define PROGRAME_DESCRIPTION "List information about the FILEs \
(the current directory by default). \
Sort entries alphabetically by default."


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
