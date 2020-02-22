/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/02/22 22:23:24 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


     // struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
     //         ino_t      d_ino;                /* file number of entry */
     //         __uint16_t d_reclen;             /* length of this record */
     //         __uint8_t  d_type;               /* file type, see below */
     //         __uint8_t  d_namlen;             /* length of string in d_name */
     //         char    d_name[255 + 1];   /* name must be no longer than this */
     // };


void	print_struct_dirent(struct dirent *dir)
{
	ft_printf("%-8d file number of entry\n", dir->d_ino);
	ft_printf("%-8d length of this record \n", dir->d_reclen);
	ft_printf("%-8d file type\n", dir->d_type);
	ft_printf("%-8d length of string in d_name\n", dir->d_namlen);
	ft_printf("%-8s name\n", dir->d_name);

}

/*
** This function will list all the file in the current directory
*/

void	list_files(char *name)
{
	DIR				*directory_infos = NULL;
	struct dirent	*file_infos;

	directory_infos = opendir(name);
	if (directory_infos)
	{
		file_infos = readdir(directory_infos);
		if (file_infos)
			print_struct_dirent(file_infos);
	}
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		list_files(av[1]);
	}
}
