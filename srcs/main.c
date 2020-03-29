/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/03/29 20:38:36 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
 ** This function will list all the files in the current directory
 */

void	list_files(char *name)
{
	DIR				*directory_infos = NULL;
	struct dirent	*file_infos;
	struct stat		statbuf;
	char			*file_path;
	int				recursive = 1;

	directory_infos = opendir(name);
	if (directory_infos)
	{
		file_infos = readdir(directory_infos);
		if (file_infos)
			while (directory_infos && file_infos)
			{
				if (file_infos)
				{
					print_struct_dirent(file_infos);
					//file_path = ft_strjoin(name, file_infos->d_name);
					file_path = file_infos->d_name;
					if (stat(file_path, &statbuf) == 0 /*SUCCESS*/)
						print_struct_stat(&statbuf);
					else
						perror(ERROR_DIR_STAT);

					if(recursive && file_infos->d_type == DT_DIR)
					{
						if (!ft_strncmp(file_infos->d_name, "..", 2)
						&& !ft_strncmp(file_infos->d_name, ".", 1))
							list_files(file_path);
						else
							ft_printf("It's . or ..\n");
					}
					else
						ft_printf("It's not a dir\n");
					//ft_strdel(&file_path);
				}
				file_infos = readdir(directory_infos);
			}
		else
			perror(ERROR_DIR_READ);
		if (closedir(directory_infos) != 0/*SUCCESS*/)
			perror(ERROR_DIR_CLOSE);
	}
	else
		perror(ERROR_DIR_OPEN);
}


int		main(int ac, char **av)
{
	if (ac > 1)
		list_files(av[1]);
	else
		list_files(DEFAULT_ARGUMENT);
}
