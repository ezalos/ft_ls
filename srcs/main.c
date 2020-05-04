/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/05/04 14:45:26 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


void	call_print(struct dirent *file_infos)
{	
	struct stat		statbuf;	

	//print_struct_dirent(file_infos);
	//file_path = ft_strjoin(name, file_infos->d_name);
	if (stat(file_infos->d_name, &statbuf) == 0 /*SUCCESS*/)
	{
		
		//n = tree_insert(n, file_infos->d_name, (int)file_infos->d_name[0]);
		//tree_inorder(n);		
//print_struct_stat(&statbuf);
		//print_ls(file_infos, statbuf);
	}
	else
		perror(ERROR_DIR_STAT);
}

int		file_check(struct dirent *file_infos)
{
	if(file_infos->d_type == DT_DIR)
	{
		if ((!ft_strncmp(file_infos->d_name, "..", 2)
			&& file_infos->d_name[2] == '\0'))
		{
			//ft_printf("Plop it's '..'\n");
			return (1);
		}
		else if ((!ft_strncmp(file_infos->d_name, ".", 1)
			&& file_infos->d_name[1] == '\0'))
		{
			//ft_printf("Plop it's '.'\n");
			return (2);
		}
		else
		{
			//ft_printf("It's a normal dir\n");		
			return (0);
		}
	}
	else
	{
		//ft_printf("It's not a dir\n");
		return (-1);
	}
}

t_sys_files	*fill_struct(struct dirent *file_infos)
{
	t_sys_files	*sys;
	int			i;

	sys = ft_memalloc(sizeof(t_sys_files));
	if (stat(file_infos->d_name, &sys->statbuf) == 0 /*SUCCESS*/)
	{
		sys->file_infos = file_infos;
		sys->check = file_check(file_infos);
		sys->key = (int)file_infos->d_name[0];
		if (sys->check == 1)
			sys->key = -1;
		else if (sys->check == 2)
			sys->key = -2;
		sys->name = ft_strdup(file_infos->d_name);
		i = -1;
		while (sys->name[++i])
			sys->name[i] = ft_tolower(sys->name[i]);
		//ft_printf("%s\n", sys->name);
	}
	else
		perror(ERROR_DIR_STAT);
	return (sys);
}

void		tree_print_inorder(t_rbt *root) 
{
	if (root != NULL) 
	{
		tree_print_inorder(root->left);
		print_ls((t_sys_files*)root->content);
		tree_print_inorder(root->right); 									    
	}
}


int		sort_files(void *one, void *two)
{
	char	*name_one;
	char	*name_two;
	int		res = 0;
	
	//ft_printf("x\n");
	name_one = ((t_sys_files*)one)->name;
	name_two = ((t_sys_files*)two)->name;
	/*if (((t_sys_files*)one)->check == 2)
		return (-500);
	if (((t_sys_files*)one)->check == 1)
		return (-400);
	if (((t_sys_files*)two)->check == 2)
		return (400);
	if (((t_sys_files*)two)->check == 1)
		return (500);*/
	if (*name_one == '.')
		name_one++;
	if (*name_two == '.')
		name_two++;
	//ft_printf("X\n");
	//ft_printf("CMP %p|%p", name_one, name_two);
	res = ft_strcmp(name_one, name_two);	
	//ft_printf("CMP %s|%s -> %d\n", name_one, name_two, res);

	return (res);
}

/*
 ** This function will list all the files in the current directory
 */

void	list_files(char *name)
{
	t_rbt			*node = NULL;
	t_sys_files		*file;
	DIR				*directory_infos = NULL;
	struct dirent	*file_infos;
	//int				recursive = 0;

	directory_infos = opendir(name);
	if (!directory_infos)
	{
		perror(ERROR_DIR_OPEN);
		return ;
	}
	file_infos = readdir(directory_infos);
	if (!file_infos)
		perror(ERROR_DIR_READ);
	while (file_infos)
	{
		file = fill_struct(file_infos);
		node = tree_insert_func(node, file, &sort_files);
		//tree_print(node, 0);
		//call_print(file_infos);
		//if (file_infos)
		//	if (!file_check(file_infos) && recursive)
		//		list_files(file_infos->d_name);
		file_infos = readdir(directory_infos);
	}
	tree_print_inorder(node);
	if (closedir(directory_infos) != 0/*SUCCESS*/)
		perror(ERROR_DIR_CLOSE);
}


int		main(int ac, char **av)
{
	if (ac > 1)
		list_files(av[1]);
	else
		list_files(DEFAULT_ARGUMENT);
	//tree_print(n, 0);
}



