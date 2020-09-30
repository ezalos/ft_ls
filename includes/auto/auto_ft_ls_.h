/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ft_ls_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:46:07 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/30 10:46:07 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FT_LS__H
# define AUTO_FT_LS__H

int		sort_files_alpha(void *one, void *two);
int		sort_files_alpha(void *one, void *two);
int		sort_files_time(void *one, void *two);
void		init_options_and_arguments(void);
int		main(int ac, char **av);
void		play_game(t_arena *arena);
int		snake(void);
void		init_snake(t_arena *arena);
void		init_board(t_arena *arena);
void		fast_terminal(float time, int size, int on_off);
void		cheat_func(t_arena *arena);
int		input_move(t_arena *arena, int input);
int		get_input(t_arena *arena);
void		snk_print_pxl(int type);
void		snk_update_pxl(int row, int col, int type);
void		snk_print(t_arena *arena);
void		get_bigger(t_arena *arena, t_coor add_spot);
char		check_move(t_coor *new, t_coor *old, t_arena *arena);
void		move_on(t_arena *arena, t_coor check_spot);
void		move_snake(t_arena *arena);
void		increase_speed(t_arena *arena);
void		change_type(t_arena *arena, t_coor *change, char type);
void		create_random(t_arena *arena, int *row, int *col);
void		fill_random(t_arena *arena, t_coor *coor, char type);
void		print_file_type(struct stat sb);
int		extended_attr(t_sys_files *file, uint8_t print);
int		extended_attr(t_sys_files *file, uint8_t print);
void		print_file_mode(struct stat sb, t_sys_files *file);
int		print_ls(t_rbt *node);
int		print_ls_l(t_rbt *node);
void		ls_output(t_rbt *node);
void		print_human_size(size_t size, float save);
void		print_file_size(size_t file_size, uint8_t format);
long long		tree_sum_size_inorder(t_rbt *root);
void		print_folder_size(t_rbt *node);
uint32_t		read_magic_number(char *path);
void		print_file_color(struct stat sb, char *path);
void		print_file_name(char *name);
void		print_file_ownership(struct stat sb);
int		check_file_time(time_t file_time);
void		print_file_last_modif(struct stat sb);
int		get_format(t_ls_format *new_format, int field);
void		update_format_ug(t_sys_files *file, t_ls_format *format);
void		update_format(t_sys_files *file, t_ls_format *format);
void		print_file_link(t_sys_files *file);
void		print_file_link_count(struct stat sb);
int		recursive(t_rbt *node);
int		one_level(t_sys_files *unix_file);
t_sys_files		*file_struct(char *name, t_sys_files *parent);
void		free_file_struct(void **content);
t_rbt		*list_files(t_sys_files *daddy);

#endif
