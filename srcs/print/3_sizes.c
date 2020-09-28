/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_sizes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:49:16 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 12:21:22 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_human_size(size_t size, float save)
{
	int			shift;

	shift = 3;
	if (size == 1)
		ft_printf("%*.*f", shift + 1, 0, save);
	else
	{
		ft_printf("%*.*f", shift, (save < 10), save);
		if (size == 2)
			ft_printf("K");
		else if (size == 3)
			ft_printf("M");
		else if (size == 4)
			ft_printf("G");
		else if (size == 5)
			ft_printf("T");
	}
}

void	print_file_size(size_t file_size, uint8_t format)
{
	long long	size;
	float		save;
	int			unit;

	if (!parse_get("human-size"))
	{
		if (format == FALSE)
			ft_printf("%llu", file_size);
		else
			ft_printf("%*llu", get_format(NULL, FORMAT_F_SIZE), file_size);
		return ;
	}
	size = 1;
	unit = 1024;
	save = file_size;
	while (save > unit)
	{
		save = save / unit;
		size++;
	}
	print_human_size(size, save);
}

long long		tree_sum_size_inorder(t_rbt *root)
{
	long long		value = 0;

	if (root != NULL)
		value += ((t_sys_files*)root->content)->statbuf.st_blocks * 512;
	return value;
}

void	print_folder_size(t_rbt *node)
{
	long long	sum = tree_inorder_long_long(node, &tree_sum_size_inorder);

	ft_printf("total ");
	print_file_size(sum / 1024, FALSE);
	ft_printf("\n");

}
