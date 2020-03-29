/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ft_ls_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 20:21:03 by ezalos            #+#    #+#             */
/*   Updated: 2020/03/29 20:21:03 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_FT_LS__H
# define AUTO_FT_LS__H

void		print_struct_dirent_d_type(struct dirent *dir);
void		print_struct_dirent(struct dirent *dir);
void		print_struct_stat(struct stat *stat);
void		list_files(char *name);
int		main(int ac, char **av);

#endif
