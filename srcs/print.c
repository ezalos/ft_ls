/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:19:42 by ezalos            #+#    #+#             */
/*   Updated: 2020/03/29 20:22:36 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

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

void	print_struct_stat(struct stat *stat)
{
	ft_printf("%s %d\n", "/* ID of device containing file */", stat->st_dev);
	ft_printf("%s %d\n", "/* Inode number */", stat->st_ino);
	ft_printf("%s %d\n", "/* File type and mode */", stat->st_mode);
	ft_printf("%s %d\n", "/* Number of hard links */", stat->st_nlink);
	ft_printf("%s %d\n", "/* User ID of owner */", stat->st_uid);
	ft_printf("%s %d\n", "/* Group ID of owner */", stat->st_gid);
	ft_printf("%s %d\n", "/* Device ID (if special file) */", stat->st_rdev);
	ft_printf("%s %d\n", "/* Total size, in bytes */", stat->st_size);
	ft_printf("%s %d\n", "/* Block size for filesystem I/O */", stat->st_blksize);
	ft_printf("%s %d\n", "/* Number of 512B blocks allocated */", stat->st_blocks);
	ft_printf("%s %d\n", "/* Time of last access */", stat->st_atim);
	ft_printf("%s %d\n", "/* Time of last modification */", stat->st_mtim);
	ft_printf("%s %d\n", "/* Time of last status change */", stat->st_ctim);
	ft_printf("\n");
}


