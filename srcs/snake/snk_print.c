#include "head.h"

void	snk_print_pxl(int type)
{
	if      (type == SNK_FOOD)
		ft_printf("%~{b255;155;155}");
	else if (type == SNK_SNAKE)
		ft_printf("%~{b155;255;155}");
	else if (type == SNK_DEAD)
		ft_printf("%~{b100;255;100}");
	else if (type == SNK_EMPTY)
		ft_printf("%~{b155;155;255}");
	else if (type == SNK_WALL)
		ft_printf("%~{b255;155;255}");
	else
	{
		ft_printf("%~{155;155;155}?%~{}");
		return ;
	}
	ft_printf("  ", type);
	ft_printf("%~{}");
}

void	snk_update_pxl(int row, int col, int type)
{
	int start_row;
	int start_col;

	start_row = SNK_SHIFT_ROW;
	start_col = SNK_SHIFT_COL;
	ft_place_cursor(start_row + row, start_col + (col * 2));
	snk_print_pxl(type);
	ft_place_cursor(0, 0);
}

void	snk_print(t_arena* arena)
{
	int start_row;
	int start_col;
	int row;
	int col;

	start_row = SNK_SHIFT_ROW;
	start_col = SNK_SHIFT_COL;
	row = -1;
	while (++row < arena->height)
	{
		ft_place_cursor(start_row + row, start_col);
		col = -1;
		while (++col < arena->width)
		{
			snk_print_pxl(arena->board[row][col]);
		}
	}
}
