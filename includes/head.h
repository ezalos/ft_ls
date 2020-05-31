/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/05/18 22:25:17 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "tree.h"
# include "arg.h"
# include "libft.h"

//Both libraries are required for opendir
# include <sys/types.h>
# include <dirent.h>
# include <error.h>
# include <string.h>

typedef	struct			s_sys_files
{
	struct stat			statbuf;
	struct dirent		*file_infos;
	char				*name_lowercase;
	char				*path;
	char				*d_name;
	int					check;
	int					key;
	t_rbt				*content;
	struct s_sys_files	*parent;

}						t_sys_files;

# include "auto_ft_ls.h"

#define		CURRENT_DIR			"."
#define		CURRENT_DIR_LEN		1
#define		UP_DIR				".."
#define		UP_DIR_LEN			2

#define		IS_CURRENT_DIR		1
#define		IS_UP_DIR			2
#define		IS_DIR				0
#define		IS_FILE				-1



# define  DEBUG_ERROR_PRINT(x)	fprintf(stderr,\
		"Internal error: %s\n\tfunc: %s\n\tfile: %s\n\tline: %d\n",\
		x ,__func__, __FILE__, __LINE__)


# define DEFAULT_ARGUMENT	"."
# define ERROR_DIR_OPEN		"Error opening dir"
# define ERROR_DIR_READ		"Error reading dir"
# define ERROR_DIR_CLOSE	"Error closing dir"
# define ERROR_DIR_STAT		"Error geting stats of file"

#endif
