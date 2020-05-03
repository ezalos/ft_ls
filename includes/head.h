/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/05/03 19:11:55 by ezalos           ###   ########.fr       */
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
# include "auto_ft_ls.h"
# include <error.h>
# include <string.h>

# include "auto_ft_ls.h"

/*
 *	# define  DEBUG_ERROR_PRINT(x)	fprintf(stderr,\
 *		"Internal error: %s\n\tfunc: %s\n\tfile: %s\n\tline: %d\n",\
 *		x ,__func__, __FILE__, __LINE__)
*/

# define DEFAULT_ARGUMENT	"."
# define ERROR_DIR_OPEN		"Error opening dir"
# define ERROR_DIR_READ		"Error reading dir"
# define ERROR_DIR_CLOSE	"Error closing dir"
# define ERROR_DIR_STAT		"Error geting stats of file"

#endif
