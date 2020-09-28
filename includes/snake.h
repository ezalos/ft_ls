#ifndef SNAKE_H
# define SNAKE_H

# include <sys/select.h>
# include <curses.h>
# include <unistd.h>
# include <termios.h>

# define TRUE		1
# define FALSE		0

# define SNK_SNAKE	'@'
# define SNK_FOOD	'+'
# define SNK_EMPTY	' '
# define SNK_WALL	'#'
# define SNK_DEAD	'x'

# define WIDTH		32
# define HEIGHT		18

/*
** ORIGINAL GAME SIZE
**
** # define WIDTH		16
** # define HEIGHT		9
*/

# define SNK_SHIFT_ROW		2
# define SNK_SHIFT_COL		4

# define SNK_ROW	0
# define SNK_COL	1

# define SNK_RIGHT	4414235
# define SNK_DOWN	4348699
# define SNK_LEFT	4479771
# define SNK_UP		4283163

# define SEED_MAX	123456789

typedef struct		s_coor
{
	int				row;
	int				col;
}					t_coor;

typedef struct		s_snake
{
	t_list			*body;
	int				len;

}					t_snake;

typedef struct		s_arena
{
	int				width;
	float			speed;
	int				height;
	int				move[2];
	int				total_size;
	char			**board;
	t_snake			*snake;
	t_coor			food;
	int				game_over;

}					t_arena;

#endif
