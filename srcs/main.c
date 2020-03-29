/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/03/29 19:06:09 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#define DEFAULT_ARGUMENT	"."

void	print_struct_dirent_d_type(struct dirent *dir)
{
	ft_printf("%d ", dir->d_type);
	if (dir->d_type == DT_BLK)
		ft_printf("{Block device}");
	else if (dir->d_type == DT_CHR)
		ft_printf("{Character device}");
	else if (dir->d_type == DT_DIR)
		ft_printf("{Directory}");
	else if (dir->d_type == DT_FIFO)
		ft_printf("{Named pipe}");
	else if (dir->d_type == DT_LNK)
		ft_printf("{Symbolic Link}");
	else if (dir->d_type == DT_REG)
		ft_printf("{Regular file}");
	else if (dir->d_type == DT_SOCK)
		ft_printf("{UNIX Domain socket}");
	else if (dir->d_type == DT_UNKNOWN)
		ft_printf("{Unknown}");
	ft_printf(" ");
}

void	print_struct_dirent(struct dirent *dir)
{
	//if (_DIRENT_HAVE_D_NAMLEN)
	//	ft_printf("%-8d length of string in d_name\n", dir->d_namlen);
	//else
	ft_printf("[%3d]", ft_strlen(dir->d_name));
	ft_printf("\"%-15s\" ", dir->d_name);
	ft_printf("#%-8d ", dir->d_ino);
	ft_printf("%3dlen ", dir->d_reclen);
	print_struct_dirent_d_type(dir);
	ft_printf("\n");
}

/*
 ** This function will list all the files in the current directory
 */
#define ERROR_DIR_OPEN	"Error opening dir"
#define ERROR_DIR_READ	"Error reading dir"
#define ERROR_DIR_CLOSE	"Error closing dir"
#include <error.h>
#include <string.h>

void	list_files(char *name)
{
	DIR				*directory_infos = NULL;
	struct dirent	*file_infos;

	directory_infos = opendir(name);
	if (directory_infos)
	{
		file_infos = readdir(directory_infos);
		if (file_infos)
			while (directory_infos && file_infos)
			{
				if (file_infos)
					print_struct_dirent(file_infos);
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
