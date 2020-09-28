#include "head.h"

void			get_bigger(t_arena *arena, t_coor add_spot)
{
	t_list	*new;
	t_coor	*coor;
	t_coor	food;

	coor = ft_memalloc(sizeof(t_coor));
	coor->row = add_spot.row;
	coor->col = add_spot.col;
	new = ft_lstnew(coor, sizeof(t_coor*));
	ft_lstadd_start(&(arena->snake->body), new);
	change_type(arena, ((t_coor*)new->content), SNK_SNAKE);
	ft_place_cursor(arena->height + SNK_SHIFT_ROW, (arena->width * 2) + SNK_SHIFT_COL - 4 - ft_nb_len(arena->snake->len, 10));
	ft_printf("LVL %-3d\n", arena->snake->len);
	fill_random(arena, &food, SNK_FOOD);
	if (1)
		fill_random(arena, &food, SNK_FOOD);
	arena->snake->len += 1;
	increase_speed(arena);
}

char		check_move(t_coor *new, t_coor *old, t_arena *arena)
{
	new->row = old->row + arena->move[SNK_ROW];
	new->col = old->col + arena->move[SNK_COL];
	if (new->row < 0)
		new->row = arena->height - 1;
	else if (new->row >= arena->height)
		new->row = 0;
	if (new->col < 0)
		new->col = arena->width - 1;
	else if (new->col >= arena->width)
		new->col = 0;
	return (arena->board[new->row][new->col]);
}


void		move_on(t_arena *arena, t_coor check_spot)
{
	t_list		*to_move;

	to_move = ft_lstcut(&(arena->snake->body), -1);
	change_type(arena, ((t_coor*)to_move->content), SNK_EMPTY);
	((t_coor*)to_move->content)->row = check_spot.row;
	((t_coor*)to_move->content)->col = check_spot.col;
	if (arena->snake->len > 1)
		ft_lstadd_start(&(arena->snake->body), to_move);
	change_type(arena, ((t_coor*)to_move->content), SNK_SNAKE);
}

void	move_snake(t_arena *arena)
{
	t_coor		check_spot;
	char		spot;

	spot = check_move(&check_spot, arena->snake->body->content, arena);
	if (spot == SNK_FOOD)
		get_bigger(arena, check_spot);
	else if (spot == SNK_SNAKE)
	{
		arena->game_over = TRUE;
		change_type(arena, &check_spot, SNK_DEAD);
	}
	else
		move_on(arena, check_spot);
}
