/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/05/06 20:33:46 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "tree.h"
# include "libft.h"
// ./../libft/includes/

//Both libraries are required for opendir
# include <sys/types.h>
# include <dirent.h>
# include <error.h>
# include <string.h>

typedef	struct			s_sys_files
{
	struct stat			statbuf;
	struct dirent		*file_infos;
	char				*name;
	char				*path;
	char				*d_name;
	int					check;
	int					key;
	t_rbt				*content;
	struct s_sys_files	*parent;

}						t_sys_files;

# include "auto_ft_ls.h"


# define  DEBUG_ERROR_PRINT(x)	fprintf(stderr,\
		"Internal error: %s\n\tfunc: %s\n\tfile: %s\n\tline: %d\n",\
		x ,__func__, __FILE__, __LINE__)


# define DEFAULT_ARGUMENT	"."
# define ERROR_DIR_OPEN		"Error opening dir"
# define ERROR_DIR_READ		"Error reading dir"
# define ERROR_DIR_CLOSE	"Error closing dir"
# define ERROR_DIR_STAT		"Error geting stats of file"

#endif
