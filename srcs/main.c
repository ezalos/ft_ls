/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/05/18 20:17:27 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		sort_files(void *one, void *two)
{
	char	*name_one;
	char	*name_two;
	int		res = 0;

	name_one = ((t_sys_files*)one)->name;
	name_two = ((t_sys_files*)two)->name;
	if (*name_one == '.')
		name_one++;
	if (*name_two == '.')
		name_two++;
	res = ft_strcmp(name_one, name_two);	

	return (res);
}

int		file_check(struct dirent *file_infos)
{
	if(file_infos->d_type == DT_DIR)
	{
		if ((!ft_strncmp(file_infos->d_name, UP_DIR, UP_DIR_LEN)
					&& file_infos->d_name[UP_DIR_LEN] == '\0'))
			return (IS_UP_DIR);
		else if ((!ft_strncmp(file_infos->d_name, CURRENT_DIR, CURRENT_DIR_LEN)
					&& file_infos->d_name[CURRENT_DIR_LEN] == '\0'))
			return (IS_CURRENT_DIR);
		else
			return (IS_DIR);
	}
	else
		return (IS_FILE);
}

t_sys_files	*origin_struct(char *name)
{
	t_sys_files	*sys;
	int			i;

	sys = ft_memalloc(sizeof(t_sys_files));

	if (lstat(name, &sys->statbuf) != 0 /*SUCCESS*/)
	{
		perror(ERROR_DIR_STAT);
		return (NULL);
	}

	sys->d_name = name;

	if (S_IFDIR == (sys->statbuf.st_mode & S_IFMT)) // IS DIR
		sys->check = IS_DIR;
	else
		sys->check = IS_FILE;

	sys->path = ft_strdup(sys->d_name);
	sys->name = ft_strdup(sys->d_name);
	i = -1;
	while (sys->name[++i])
		sys->name[i] = ft_tolower(sys->name[i]);
	return (sys);
}

t_sys_files	*fill_struct(struct dirent *file_infos, t_sys_files *parent)
{
	t_sys_files	*sys;
	int			i;

	sys = ft_memalloc(sizeof(t_sys_files));
	sys->parent = parent;
	sys->file_infos = file_infos;
	sys->d_name = ft_strdup(file_infos->d_name);
	sys->path = ft_strjoin(sys->parent->path, ft_strdup("/"));
	sys->path = ft_strjoin(sys->path, sys->d_name);
	sys->check = file_check(file_infos);
	if (lstat(sys->path, &sys->statbuf) != 0 /*SUCCESS*/)
	{
		perror(ERROR_DIR_STAT);
		ft_printf("%s\n", sys->d_name);
	}
	sys->name = ft_strdup(sys->d_name);
	i = -1;
	while (sys->name[++i])
		sys->name[i] = ft_tolower(sys->name[i]);
	return (sys);
}

/*
 ** This function will list all the files in the current directory
 */

t_rbt	*list_files(t_sys_files *daddy)
{
	t_rbt			*node = NULL;
	t_sys_files		*file;
	DIR				*directory_infos = NULL;
	struct dirent	*file_infos;

	directory_infos = opendir(daddy->path);
	if (directory_infos)
	{
		file_infos = readdir(directory_infos);
		if (file_infos)
			while (file_infos)
			{
				file = fill_struct(file_infos, daddy);
				node = tree_insert_func(node, file, &sort_files);
				file_infos = readdir(directory_infos);
			}
		else
			perror(ERROR_DIR_READ);
		if (closedir(directory_infos) != 0/*SUCCESS*/)
			perror(ERROR_DIR_CLOSE);
	}
	else
		perror(ERROR_DIR_OPEN);
	return (node); //free all?
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
	ls_output(node);
	if (parse_get("Recurse"))
	{
		tree_inorder(node, &recursive);
	}
	return (1);
}

# define PROGRAME_DESCRIPTION "List information about the FILEs (the current directory by default). Sort entries alphabetically by default."


int		main(int ac, char **av)
{
	t_sys_files	*file;

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
	//arg_print();

	ft_printf("ARG: %s\n",parse_get("PATH")->raw[0]);
	if (parse_get("help") != NULL)
		return (parse_usage());
	if (parse_get("PATH") != NULL)
		file = origin_struct(parse_get("PATH")->raw[0]);
	else
		file = origin_struct(DEFAULT_ARGUMENT);
	if (file && 0)
		one_level(file);
	return (0);
}


