/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ft_ls_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:51:48 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/03 16:16:30 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FT_LS__H
# define AUTO_FT_LS__H

void			change_type(t_arena *arena, t_coor *change, char type);
void			cheat_func(t_arena *arena);
int				check_file_time(time_t file_time);
char			check_move(t_coor *new, t_coor *old, t_arena *arena);
void			create_random(t_arena *arena, int *row, int *col);
int				extended_attr(t_sys_files *file, uint8_t print);
int				extended_attr(t_sys_files *file, uint8_t print);
void			fast_terminal(float time, int size, int on_off);
int8_t			file_data_creation(t_sys_files *unix_file, t_rbt **node);
t_sys_files		*file_struct(char *name, t_sys_files *parent);
void			fill_random(t_arena *arena, t_coor *coor, char type);
void			free_file_struct(void **content);
void			free_memory(t_sys_files *unix_file,
				t_rbt *node,
				int8_t to_free);
void			get_bigger(t_arena *arena, t_coor add_spot);
int				get_format(t_ls_format *new_format, int field);
int				get_input(t_arena *arena);
void			increase_speed(t_arena *arena);
void			init_board(t_arena *arena);
void			init_options_and_arguments(void);
void			init_snake(t_arena *arena);
int				input_move(t_arena *arena, int input);
int8_t			is_file_dir(struct stat sb);
t_rbt			*list_files(t_sys_files *daddy);
void			ls_multi_path(int ac, char **av);
void			ls_output(t_rbt *node);
void			ls_output_list(t_rbt *node);
void			ls_print_path(t_rbt *node);
int				main(int ac, char **av);
void			move_on(t_arena *arena, t_coor check_spot);
void			move_snake(t_arena *arena);
int				one_level(t_sys_files *unix_file);
void			play_game(t_arena *arena);
void			print_file_color(struct stat sb, char *path);
void			print_file_last_modif(struct stat sb);
void			print_file_link(t_sys_files *file);
void			print_file_link_count(struct stat sb);
void			print_file_mode(struct stat sb, t_sys_files *file);
void			print_file_name(char *name);
void			print_file_ownership(struct stat sb);
void			print_file_size(size_t file_size, uint8_t format);
void			print_file_type(struct stat sb);
void			print_folder_size(t_rbt *node);
void			print_human_size(size_t size, float save);
int				print_ls(t_rbt *node);
int				print_ls_l(t_rbt *node);
uint32_t		read_magic_number(char *path);
int				recursive(t_rbt *node);
int				snake(void);
void			snk_print(t_arena *arena);
void			snk_print_pxl(int type);
void			snk_update_pxl(int row, int col, int type);
int				sort_files_alpha(void *one, void *two);
int				sort_files_alpha(void *one, void *two);
int				sort_files_time(void *one, void *two);
intmax_t		tree_sum_size_inorder(t_rbt *root);
void			update_format(t_sys_files *file, t_ls_format *format);
void			update_format_ug(t_sys_files *file, t_ls_format *format);

#endif
