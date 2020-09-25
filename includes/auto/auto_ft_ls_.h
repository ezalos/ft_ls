/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ft_ls_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:22:45 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/25 18:22:45 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FT_LS__H
# define AUTO_FT_LS__H

int		get_format(t_ls_format *new_format, int field);
uint32_t		read_magic_number(char *path);
void		print_file_color(struct stat sb, char *path);
void		print_file_type(struct stat sb);
int		extended_attr(t_sys_files *file);
void		print_file_mode(struct stat sb, t_sys_files *file);
void		print_file_ownership(struct stat sb);
void		print_file_size(size_t file_size);
void		print_file_link_count(struct stat sb);
int		check_file_time(time_t file_time);
void		print_file_name(char *name);
void		print_file_link(t_sys_files *file);
int		print_ls(t_rbt *node);
int		print_ls_l(t_rbt *node);
int		tree_sum_size_inorder(t_rbt *root);
void		ls_output(t_rbt *node);
int		sort_files_alpha(void *one, void *two);
int		sort_files_alpha(void *one, void *two);
int		sort_files_time(void *one, void *two);
int		recursive(t_rbt *node);
int		one_level(t_sys_files *unix_file);
int		main(int ac, char **av);
void		update_format(t_sys_files *file, t_ls_format *format);
t_sys_files		*file_struct(char *name, t_sys_files *parent);
t_rbt		*list_files(t_sys_files *daddy);

#endif
