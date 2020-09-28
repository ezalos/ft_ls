/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_file_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:51:33 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 15:34:21 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_file_link(t_sys_files *file)
{
	struct stat		stat_link;
	char			buf[500];
	int				color;

	if (S_IFLNK == (file->statbuf.st_mode & S_IFMT))
	{
		color = 0;
		if (stat(file->path, &stat_link) != 0 /*SUCCESS*/)
		{
			// ft_printf("%s\n", file->path);
			// perror(ERROR_DIR_STAT);
			color = 1;
		}
		ft_bzero(buf, 500);
		if (readlink(file->path, buf, 500) == -1)
			return ;
		ft_printf(" -> ");
		if (color)
			print_file_color(stat_link, buf);
		print_file_name(buf);
		if (color)
			ft_printf("%~{}");
	}
}
