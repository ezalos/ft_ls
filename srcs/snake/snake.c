#include "head.h"

void		play_game(t_arena *arena)
{
	_C_CLEAR_SCREEN;
	snk_print(arena);
	while (arena->game_over == FALSE)
	{
		get_input(arena);
		move_snake(arena);
	}
	ft_place_cursor(arena->height + SNK_SHIFT_ROW + 1, SNK_SHIFT_COL);
	ft_printf("Sorry you lost baby....\n");
}

int 		snake(void)
{
	t_arena	arena;

	init_board(&arena);
	init_snake(&arena);
	play_game(&arena);
	return (0);
}
