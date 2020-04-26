/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ft_ls_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:03:36 by ezalos            #+#    #+#             */
/*   Updated: 2020/04/26 21:03:36 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FT_LS__H
# define AUTO_FT_LS__H

void		print_struct_dirent_d_type(struct dirent *dir);
void		print_struct_dirent(struct dirent *dir);
void		print_struct_stat(struct stat *stat);
void		print_file_type(struct stat sb);
void		print_file_mode(struct stat sb);
void		print_file_ownership(struct stat sb);
void		print_file_size(struct stat sb);
void		print_file_name(struct dirent *dir, struct stat sb);
void		print_ls(struct dirent *file_infos, struct stat statbuf);
void		call_print(struct dirent *file_infos);
int		file_check(struct dirent *file_infos);
void		list_files(char *name);
int		main(int ac, char **av);

#endif
