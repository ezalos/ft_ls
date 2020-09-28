/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snk_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:15:02 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 11:30:11 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		fast_terminal(float time, int size, int on_off)
{
	static struct termios	old = {0};

	if (on_off)
	{
		if (tcgetattr(0, &old) < 0)
			perror("tcsetattr()");
		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = size;
		old.c_cc[VTIME] = time;
		if (tcsetattr(0, TCSANOW, &old) < 0)
			perror("tcsetattr ICANON");
	}
	else
	{
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		if (tcsetattr(0, TCSADRAIN, &old) < 0)
			perror("tcsetattr ~ICANON");
	}
}

void	cheat_func(t_arena *arena)
{
	t_coor		add_spot;
	t_list		*new;
	t_coor		*coor;

	check_move(&add_spot, arena->snake->body->content, arena);
	coor = ft_memalloc(sizeof(t_coor));
	coor->row = add_spot.row;
	coor->col = add_spot.col;
	new = ft_lstnew(coor, sizeof(t_coor*));
	ft_lstadd_start(&(arena->snake->body), new);
	change_type(arena, ((t_coor*)new->content), SNK_SNAKE);
	arena->snake->len += 1;
	increase_speed(arena);
}


int 	get_input(t_arena *arena)
{
	int	input;

	input = 0;
	fast_terminal(arena->speed, 0, 1);
	read(0, (char*)&input, 3);
	fast_terminal(arena->speed, 0, 0);
	if ((input == SNK_UP
	||  input == 'w') && arena->move[SNK_ROW] == 0)
	{
		arena->move[SNK_ROW] = -1;
		arena->move[SNK_COL] = 0;
	}
	else if ((input == SNK_DOWN
		 ||  input == 's') && arena->move[SNK_ROW] == 0)
	{
		arena->move[SNK_ROW] = 1;
		arena->move[SNK_COL] = 0;
	}
	else if ((input == SNK_LEFT
		 ||  input == 'a') && arena->move[SNK_COL] == 0)
	{
		arena->move[SNK_ROW] = 0;
		arena->move[SNK_COL] = -1;
	}
	else if ((input == SNK_RIGHT
		 ||  input == 'd') && arena->move[SNK_COL] == 0)
	{
		arena->move[SNK_ROW] = 0;
		arena->move[SNK_COL] = 1;
	}
	else if (input == ' ')
	{
		fast_terminal(0, 1, 1);
		ft_press_any_key();
		fast_terminal(0, 1, 0);
	}
	else if (input == 'c')
		cheat_func(arena);
	else if (input == '\\')
		snk_print(arena);
	else if (input == 27)//escape key
		arena->game_over = 1;
	return (0);
}
