/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/04/26 22:22:12 by ezalos           ###   ########.fr       */
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
		//print_struct_stat(&statbuf);
		print_ls(file_infos, statbuf);
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


/*
 ** This function will list all the files in the current directory
 */

void	list_files(char *name)
{
	DIR				*directory_infos = NULL;
	struct dirent	*file_infos;
	int				recursive = 0;

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
		call_print(file_infos);
		if (file_infos)
			if (!file_check(file_infos) && recursive)
				list_files(file_infos->d_name);
		file_infos = readdir(directory_infos);
	}
	if (closedir(directory_infos) != 0/*SUCCESS*/)
		perror(ERROR_DIR_CLOSE);
}


int		main(int ac, char **av)
{
	if (ac > 1)
		list_files(av[1]);
	else
		list_files(DEFAULT_ARGUMENT);
}



