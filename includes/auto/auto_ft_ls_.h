/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ft_ls_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:09:19 by ezalos            #+#    #+#             */
/*   Updated: 2020/05/03 19:12:59 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FT_LS__H
# define AUTO_FT_LS__H

void		print_struct_dirent_d_type(struct dirent *dir);
void		print_struct_dirent(struct dirent *dir);
void		print_struct_stat(struct stat *stat);
void		print_file_color(struct stat sb);
void		print_file_type(struct stat sb);
void		print_file_mode(struct stat sb);
void		print_file_ownership(struct stat sb);
void		print_file_size(struct stat sb);
void		print_file_link_count(struct stat sb);
void		print_file_name(struct dirent *dir, struct stat sb);
void		print_ls(struct dirent *file_infos, struct stat statbuf);
void		call_print(struct dirent *file_infos);
int		file_check(struct dirent *file_infos);
void		list_files(char *name);
int		main(int ac, char **av);
t_rbt		*tree_new_node(void *content);
t_rbt		*tree_parent(t_rbt *node);
t_rbt		*tree_root(t_rbt *node);
t_rbt		*tree_sibling(t_rbt *node);
t_rbt		*tree_uncle(t_rbt *node);
void		tree_rot_left(t_rbt *node);
void		tree_rot_right(t_rbt *node);
void		tree_recoloring(t_rbt *node);
void		tree_insert_recurse(t_rbt *root, t_rbt *n);
void		tree_insert_case_1(t_rbt *n);
void		tree_insert_case_2(t_rbt *n);
void		tree_insert_case_3(t_rbt *n);
void		tree_insert_case_4(t_rbt *n);
void		tree_insert_repair(t_rbt *n);
t_rbt		*tree_insert(t_rbt *root, void* content, t_rbt_compare func);
void		tree_inorder(t_rbt *root); 
void		padding_before(t_rbt *node, size_t space);
void		padding_after(t_rbt *node);
void		tree_print(t_rbt *node, size_t deep);

#endif