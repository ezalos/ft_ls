/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:50:34 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 10:37:43 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int					get_format(t_ls_format *new_format, int field)
{
	static t_ls_format	*format;
	int					value;

	if (new_format)
		format = new_format;
	value = 0;
	if (format && field >= 0 && field <= 6)
		value = ((int*)format)[field];
	return (value);
}

void				update_format_ug(t_sys_files *file, t_ls_format *format)
{
	int					len;
	struct passwd		*pw;
	struct group		*grp;

	pw = getpwuid(file->statbuf.st_uid);
	if (pw)
		len = ft_strlen(pw->pw_name);
	else
		len = ft_nb_len(file->statbuf.st_uid, 10);
	if (len > format->u_name)
		format->u_name = len;
	grp = getgrgid(file->statbuf.st_gid);
	if (grp)
		len = ft_strlen(grp->gr_name);
	else
		len = ft_nb_len(file->statbuf.st_gid, 10);
	if (len > format->g_name)
		format->g_name = len;
}

void				update_format(t_sys_files *file, t_ls_format *format)
{
	int					len;

	if (extended_attr(file, FALSE))
		format->rights = 1;
	len = ft_u_nb_len(file->statbuf.st_nlink, 10);
	if (len > format->links)
		format->links = len;
	update_format_ug(file, format);
	len = ft_u_nb_len(file->statbuf.st_size, 10);
	if (len > format->size)
		format->size = len;
}
