/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_owner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:58:06 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 10:38:09 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_file_ownership(struct stat sb)
{
	struct passwd	*pw;
	struct group	*grp;

	pw = getpwuid(sb.st_uid);
	if (pw)
		ft_printf("%-*s ", get_format(NULL, FORMAT_U_NAME), pw->pw_name);
	else
		ft_printf("~%-*lld ", get_format(NULL, FORMAT_U_NAME) - 1, sb.st_uid);
	grp = getgrgid(sb.st_gid);
	if (grp)
		ft_printf("%-*s ", get_format(NULL, FORMAT_G_NAME), grp->gr_name);
	else
		ft_printf("~%-*lld ", get_format(NULL, FORMAT_G_NAME) - 1, sb.st_gid);
}
