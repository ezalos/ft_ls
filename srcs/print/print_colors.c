/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:53:04 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 10:43:20 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

uint32_t	read_magic_number(char *path)
{
	char			magic_number[4];
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		ft_bzero(magic_number, 4);
		read(fd, (char*)magic_number, MAGIC_NUMBER_LEN);
		close(fd);
	}
	return (*(uint32_t*)magic_number);
}

void		print_file_color(struct stat sb, char *path)
{
	uint32_t		file_type;

	if (S_IFBLK == (sb.st_mode & S_IFMT))
		ft_printf("%~{150;255;255}");
	else if (S_IFCHR == (sb.st_mode & S_IFMT))
		ft_printf("%~{255;150;255}");
	else if (S_IFDIR == (sb.st_mode & S_IFMT))
		ft_printf("%~{255;255;150}");
	else if (S_IFIFO == (sb.st_mode & S_IFMT))
		ft_printf("%~{150;150;255}");
	else if (S_IFLNK == (sb.st_mode & S_IFMT))
		ft_printf("%~{255;150;150}");
	else if (S_IFREG == (sb.st_mode & S_IFMT))
	{
		file_type = read_magic_number(path);
		if (file_type == MAGIC_NUMBER_ELF || 1 & (sb.st_mode >> 0)
		|| 1 & (sb.st_mode >> 3) || 1 & (sb.st_mode >> 6))
			ft_printf("%~{220;125;255}");
		else
			ft_printf("%~{}");
	}
	else if (S_IFSOCK == (sb.st_mode & S_IFMT))
		ft_printf("%~{255;150;255}");
	else
		ft_printf("%~{255;255;150}");
}
