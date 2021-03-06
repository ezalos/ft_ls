/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/01 22:00:31 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "libft.h"

/*
** Both libraries are required for opendir
*/

# include <sys/types.h>
# include <dirent.h>

# if __linux__
#  include <error.h>
#  define OS_IS_LINUX		1

# elif __MACH__
#  define OS_IS_LINUX		0

# else
#  define OS_IS_LINUX		-1

# endif

# include <string.h>

/*
** reading rights of file (user/groupe)
*/

# include <grp.h>
# include <pwd.h>

# include <sys/types.h>
# if __MACH__
#  include <sys/acl.h>
# endif

# include "ls_structs.h"
# include "snake.h"
# include "auto_ft_ls.h"

# include <sys/xattr.h>

# define TIMESTR_MON		1
# define TIMESTR_DAY		2
# define TIMESTR_HOU		3
# define TIMESTR_YEA		4

# define FORMAT_RIGHTS		0
# define FORMAT_F_LINK		1
# define FORMAT_U_NAME		2
# define FORMAT_G_NAME		3
# define FORMAT_F_SIZE		4
# define FORMAT_T_HOUR		5
# define FORMAT_T_YEAR		6

# define CURRENT_DIR		"."
# define CURRENT_DIR_LEN	1
# define UP_DIR				".."
# define UP_DIR_LEN			2

# define IS_CURRENT_DIR		1
# define IS_UP_DIR			2
# define IS_DIR				0
# define IS_FILE			-1

# define MAGIC_NUMBER_LEN		4
# if __linux__
#  define MAGIC_NUMBER_ELF		0x464c457f
# elif __MACH__
#  define MAGIC_NUMBER_ELF		0xfeedfacf
# endif

# define DEFAULT_ARGUMENT	"."
# define ERROR_DIR_OPEN		"Error opening dir"
# define ERROR_DIR_READ		"Error reading dir"
# define ERROR_DIR_CLOSE	"Error closing dir"
# define ERROR_DIR_STAT		"Error geting stats of file"

#endif
