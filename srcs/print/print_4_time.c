/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_4_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:53:58 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/01 21:11:14 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int				check_file_time(time_t file_time)
{
	static time_t	now;
	long long		old_file;

	if (!now)
		now = time(NULL);
	old_file = 60.0 * 60.0 * 24.0 * (31.0 * 6.0 - 3.4);
	if (OS_IS_LINUX)
	{
		if (file_time > now + 3600)
			return (TRUE);
	}
	else
	{
		if (file_time > now + old_file)
			return (TRUE);
	}
	if ((unsigned long long)file_time < (unsigned long long)now - old_file)
		return (TRUE);
	return (FALSE);
}

static void		print_time_dic(struct stat sb, char **time_dic)
{
	if (OS_IS_LINUX)
	{
		ft_printf("%-5s ", time_dic[TIMESTR_MON], time_dic[TIMESTR_DAY]);
		ft_printf("%2s ", time_dic[TIMESTR_DAY]);
	}
	else
	{
		ft_printf("%2s ", time_dic[TIMESTR_DAY]);
		ft_printf("%-5s ", time_dic[TIMESTR_MON]);
	}
	if (check_file_time(sb.st_mtime) || time_dic[TIMESTR_YEA][0] != '2')
		ft_printf(" %04s ", time_dic[TIMESTR_YEA]);
	else
		ft_printf("%.5s ", time_dic[TIMESTR_HOU]);
}

void			print_file_last_modif(struct stat sb)
{
	char			*no_newline;
	char			**time_dic;
	int				i;

	no_newline = ctime(&sb.st_mtime);
	i = -1;
	while (no_newline[++i])
		if (no_newline[i] == '\n')
			no_newline[i] = ' ';
	time_dic = ft_strsplit(no_newline, ' ');
	print_time_dic(sb, time_dic);
	i = -1;
	while (time_dic[++i] != NULL)
		ft_memdel((void**)&time_dic[i]);
	ft_memdel((void**)&time_dic[i]);
	ft_memdel((void**)&time_dic);
}
