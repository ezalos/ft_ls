/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/05/06 21:02:46 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define		CURRENT_DIR		"."
#define		CURRENT_DIR_LEN	1
#define		UP_DIR			".."
#define		UP_DIR_LEN		2

#define		IS_CURRENT_DIR		1
#define		IS_UP_DIR			2
#define		IS_DIR				0
#define		IS_FILE				-1

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
	if (0)
		tree_inorder(node, &recursive);
	return (1);
}

int		main(int ac, char **av)
{
	t_sys_files	*file;

	if (ac > 1)
		file = origin_struct(av[1]);
	else
		file = origin_struct(DEFAULT_ARGUMENT);
	if (file)
		one_level(file);
	return (0);
}


