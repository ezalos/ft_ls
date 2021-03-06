/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:46:30 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 17:41:11 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#if __linux__

int		sort_files_alpha(void *one, void *two)
{
	char	*name_one;
	char	*name_two;

	name_one = ((t_sys_files*)one)->d_name;
	name_two = ((t_sys_files*)two)->d_name;
	return (ft_strcmp(name_one, name_two));
}

/*
** int		sort_files_alpha(void *one, void *two)
** {
** 	char	*name_one;
** 	char	*name_two;
**
** 	name_one = ((t_sys_files*)one)->name_lowercase;
** 	name_two = ((t_sys_files*)two)->name_lowercase;
** 	if (*name_one == '.')
** 		name_one++;
** 	if (*name_two == '.')
** 		name_two++;
** 	if (((t_sys_files*)one)->check == IS_UP_DIR)
** 	{
** 		name_one++;
** 		if (((t_sys_files*)two)->check == IS_CURRENT_DIR)
** 			return (1);
** 	}
** 	if (((t_sys_files*)two)->check == IS_UP_DIR)
** 	{
** 		name_two++;
** 		if (((t_sys_files*)one)->check == IS_CURRENT_DIR)
** 			return (-1);
** 	}
** 	return (ft_strcmp(name_one, name_two));
** }
*/

#elif __MACH__

int		sort_files_alpha(void *one, void *two)
{
	char	*name_one;
	char	*name_two;

	name_one = ((t_sys_files*)one)->d_name;
	name_two = ((t_sys_files*)two)->d_name;
	return (ft_strcmp(name_one, name_two));
}

#endif

int		sort_files_time(void *one, void *two)
{
	long long	time_one;
	long long	time_two;

	time_one = ((t_sys_files*)one)->statbuf.st_mtime;
	time_two = ((t_sys_files*)two)->statbuf.st_mtime;
	if (time_one < time_two)
		return (1);
	else if (time_one == time_two)
		return (sort_files_alpha(one, two));
	return (-1);
}
