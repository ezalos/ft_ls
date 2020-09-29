/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_0_rights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:53:03 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/29 14:49:40 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_file_type(struct stat sb)
{
	if (S_IFBLK == (sb.st_mode & S_IFMT))
		ft_printf("b");
	else if (S_IFCHR == (sb.st_mode & S_IFMT))
		ft_printf("c");
	else if (S_IFDIR == (sb.st_mode & S_IFMT))
		ft_printf("d");
	else if (S_IFIFO == (sb.st_mode & S_IFMT))
		ft_printf("p");
	else if (S_IFLNK == (sb.st_mode & S_IFMT))
		ft_printf("l");
	else if (S_IFREG == (sb.st_mode & S_IFMT))
		ft_printf("-");
	else if (S_IFSOCK == (sb.st_mode & S_IFMT))
		ft_printf("s");
	else
		ft_printf("?");
}

#if __linux__

int		extended_attr(t_sys_files *file, uint8_t print)
{
	// char		buf_list[1000];
	// ssize_t		size_list;
	int			ret;

	// ft_bzero(buf_list, 1000);
	ret = 0;
	// size_list = ;
	if (llistxattr(file->path, NULL, 0) > 0)
	{
		if (print)
			ft_printf("+");
		ret += 1;
	}
	return (ret);
}

#elif __MACH__

/*
** If the file or directory has extended attributes,
** the permissions field printed by the -l option is followed by a '@'
** character.
**
** Otherwise, if the file or directory has extended security information
** (such as an access control list), the permissions field printed by
** the -l option is followed by a '+' character.
*/

int		extended_attr(t_sys_files *file, uint8_t print)
{
	int			ret;
	acl_t		acl;
	// char 		*str;
	// ssize_t 	len_p;

	ret = 0;
	if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0)
	{
		if (print)
			ft_printf("@");
		ret += 1;
	}
	else
	{
	    acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
		if (acl)
		{
			// len_p = 1000;
			// if ((str = acl_to_text(acl, &len_p)) != NULL)
			// {
				if (print)
					ft_printf("+");
				// free(str);
				ret += 1;
				acl_free(acl);
			// }
		}
	}
	return (ret);
}

#endif

void	print_file_mode(struct stat sb, t_sys_files *file)
{
	int mode = sb.st_mode;
	int step;
	int i;

	step = 3;
	i = 3 * step;
	while (i > 0)
	{
		i -= step;
		if (4 & (mode >> i))
			ft_printf("r");
		else
			ft_printf("-");
		if (2 & (mode >> i))
			ft_printf("w");
		else
			ft_printf("-");
		if ((i == 6 && mode & S_ISUID) || (i == 3 && mode & S_ISGID))
			ft_printf("%c", (1 & (mode >> i)) ? 's' : 'S');
		else if (i == 0 && mode & S_ISVTX)
			ft_printf("%c", (1 & (mode >> i)) ? 't' : 'T');
		else
			ft_printf("%c", (1 & (mode >> i)) ? 'x' : '-');
	}
	if (!extended_attr(file, TRUE))
		ft_printf("%*s", get_format(NULL, FORMAT_RIGHTS), "");
	ft_printf(" ");
}
