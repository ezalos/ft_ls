/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:53:58 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 12:15:35 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		check_file_time(time_t file_time)
{
	static time_t	now;
	long long		old_file;

	if (!now)
		now = time(NULL);
	if (file_time > now + 3600)
		return (TRUE);
	old_file = 60.0 * 60.0 * 24.0 * (31.0 * 6.0 - 3.4);
	if ((unsigned long long)file_time < (unsigned long long)now - old_file)//1616544000)
		return (TRUE);
	return (FALSE);

}

void	print_file_last_modif(struct stat sb)
{
	char	*no_newline;
	char	**time_dic;
	int		i;

	no_newline = ctime(&sb.st_mtime);
	i = -1;
	while (no_newline[++i])
		if (no_newline[i] == '\n')
			no_newline[i] = ' ';
	time_dic = ft_strsplit(no_newline, ' ');
	ft_printf("%-5s ", time_dic[TIMESTR_MON]);
	ft_printf("%2s ", time_dic[TIMESTR_DAY]);
	if (check_file_time(sb.st_mtime) || time_dic[TIMESTR_YEA][0] != '2')
	{
		//no need for lonely file
		//if (get_format(NULL, FORMAT_T_HOUR))
		//	ft_printf(" ");
		ft_printf(" %04s ", time_dic[TIMESTR_YEA]);
	}
	else
		ft_printf("%.5s ", time_dic[TIMESTR_HOU]);
	//ft_printf("%llu-", (unsigned long long)time(NULL));
	//ft_printf("%llu=", (unsigned long long)sb.st_mtime);
	//ft_printf("%lld ", (unsigned long long)time(NULL) - (unsigned long long)sb.st_mtime);
}
