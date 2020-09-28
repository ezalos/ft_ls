/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_file_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:51:33 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 09:51:43 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_file_link(t_sys_files *file)
{
	struct stat		stat_link;
	char			*buf;
	size_t			bufsiz = 500;

	if (S_IFLNK == (file->statbuf.st_mode & S_IFMT))
	{
		if (stat(file->path, &stat_link) != 0 /*SUCCESS*/)
		{
			perror(ERROR_DIR_STAT);
			return ;
		}
		buf = ft_memalloc(bufsiz);
		if (readlink(file->path, buf, bufsiz) == -1)
			return ;
		ft_printf(" -> ");
		print_file_color(stat_link, buf);
		print_file_name(buf);
		ft_printf("%~{}");
	}
}
