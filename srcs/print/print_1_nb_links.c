/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1_nb_links.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:00:46 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 10:53:01 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_file_link_count(struct stat sb)
{
	int			shift;

	shift = get_format(NULL, FORMAT_F_LINK);
	ft_printf("%*ld ", shift, (long)sb.st_nlink);
}
