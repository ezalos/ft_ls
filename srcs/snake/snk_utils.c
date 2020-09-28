/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snk_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:45:31 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 16:46:41 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		increase_speed(t_arena *arena)
{
	if (arena->speed > 1)
	{
		arena->speed -= 1;
		arena->speed = arena->speed - (arena->speed / 5);
		arena->speed += 1;
	}
	else
		arena->speed = 1;
}

void		change_type(t_arena *arena, t_coor *change, char type)
{
	arena->board[change->row][change->col] = type;
	snk_update_pxl(change->row, change->col, type);
}

void		create_random(t_arena *arena, int *row, int *col)
{
	*row = ft_rand(arena->height, ft_seed_time(0, SEED_MAX) + *row) / 2;
	*row += ft_rand(arena->height, ft_seed_time(0, SEED_MAX) + *row) / 2;
	*col = ft_rand(arena->width, ft_seed_time(0, SEED_MAX) + *col) / 2;
	*col += ft_rand(arena->width, ft_seed_time(0, SEED_MAX) + *col) / 2;
}

void		fill_random(t_arena *arena, t_coor *coor, char type)
{
	int i;

	i = 0;
	create_random(arena, &coor->row, &coor->col);
	while (arena->board[coor->row][coor->col] != SNK_EMPTY
			&& i++ < arena->total_size)
		create_random(arena, &coor->row, &coor->col);
	change_type(arena, coor, type);
}
