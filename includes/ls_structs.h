/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:37:53 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/01 21:38:38 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_STRUCTS_H
# define LS_STRUCTS_H

typedef struct			s_ls_format
{
	int					rights;
	int					links;
	int					u_name;
	int					g_name;
	int					size;
	int					hour;
	int					year;
	int					month;
	int					day;
	int					name;
}						t_ls_format;

typedef	struct			s_sys_files
{
	struct stat			statbuf;
	struct s_ls_format	format;
	char				*name_lowercase;
	char				*path;
	char				*d_name;
	int					open_denied;
	int					check;
	int					key;
	t_rbt				*content;
	struct s_sys_files	*parent;
	int					empty_folder_case;
	int					lonely_file;

}						t_sys_files;

#endif
