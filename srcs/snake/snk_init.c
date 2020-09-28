#include "head.h"

/*
** Before starting the game, we need to position our snake
** and our food. In the structure "snake" we will have a chained
** list of all the parts of the snake's body and its total size. 
** We look for a random place to put the head of our snake with
** fill_random, then get_bigger will create the first link of our
** list with these coordinates, and also find some random
** spot for the food.
*/

void		init_snake(t_arena *arena)
{
	t_coor		new;

	arena->snake = ft_memalloc(sizeof(t_snake));
	fill_random(arena, &new, SNK_SNAKE);
	arena->snake->len = 0;
	get_bigger(arena, new);
}

/*
** In arena->board we create a tab of strings (HEIGHT * WIDTH)
** then we initiate its content to SNK_EMPTY (meaning it is
** just the background of the game, not food or snake)
*/

void		init_board(t_arena *arena)
{
	int			row;
	int			col;

	ft_bzero(arena, sizeof(t_arena));
	arena->game_over = FALSE;
	arena->width = WIDTH;
	arena->height = HEIGHT;
	arena->total_size = arena->width * arena->height;
	arena->board = ft_memalloc(sizeof(char*) * arena->height);
	arena->speed = 3.5;
	arena->move[SNK_COL] = 1;
	row = 0;
	while (row < HEIGHT)
	{
		arena->board[row] = ft_memalloc(sizeof(char) * arena->width);
		col = 0;
		while (col < WIDTH)
		{
			arena->board[row][col] = SNK_EMPTY;
			col++;
		}
		row++;
	}
}
