/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_rights.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:53:03 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/28 15:55:47 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_file_type(struct stat sb)
{
	if (S_IFBLK == (sb.st_mode & S_IFMT))
		ft_printf("b");//block device
	else if (S_IFCHR == (sb.st_mode & S_IFMT))
		ft_printf("c");//character device
	else if (S_IFDIR == (sb.st_mode & S_IFMT))
		ft_printf("d");//directory
	else if (S_IFIFO == (sb.st_mode & S_IFMT))
		ft_printf("p");//FIFO/pipe
	else if (S_IFLNK == (sb.st_mode & S_IFMT))
		ft_printf("l");//symlink
	else if (S_IFREG == (sb.st_mode & S_IFMT))
		ft_printf("-");//regular file
	else if (S_IFSOCK == (sb.st_mode & S_IFMT))
		ft_printf("s");//socket
	else
		ft_printf("?");//unknown?
}

#include <sys/types.h>
#if __MACH__
#include <sys/acl.h>
#endif

int		extended_attr(t_sys_files *file, uint8_t print)
{
	char		buf_list[1000];
	// char		buf_attr[1000];
	ssize_t		size_list;
	// ssize_t		size_attr;
	// int			len;
	int			ret;

	ft_bzero(buf_list, 1000);
	ret = 0;
#if __linux__

	size_list = llistxattr(file->path, buf_list, 1000);
	if (size_list)
	{
		if (print)
			ft_printf("+");
		ret += 1;
	}

#elif __MACH__
// If the file or directory has extended attributes,
// the permissions field printed by the -l option is followed by a '@' character.
//
// Otherwise, if the file or directory has extended security information
// (such as an access control list), the permissions field printed by
// the -l option is followed by a '+' character.

	acl_t	acl;
	char *str;
	ssize_t len_p;
	// acl_entry_t entry_p;
    acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	if (acl)
	{
		len_p = 1000;
		if ((str = acl_to_text(acl, &len_p)) != NULL)
		{
			if (print)
				ft_printf("+");
			free(str);
			ret += 1;
			acl_free(acl);
		}
	}
	size_list = listxattr(file->path, buf_list, 1000, XATTR_NOFOLLOW | XATTR_SHOWCOMPRESSION);
	if (size_list)
	{
		if (print)
			ft_printf("@");
		ret += 1;
	}

#endif

	return (ret);
	// ft_printf("List size: %d", size_list);
	// len = 0;
	// while (len < (int)size_list)
	// {
	// 	ft_bzero(buf_attr, 1000);
	// 	if ((size_attr = lgetxattr(file->path, buf_list + len, buf_attr, 1000)) > 0)
	// 	{
	// 		buf_attr[size_attr] = '\0';
	// 		ft_printf("[%s:", buf_list + len);
	// 		ft_printf("%d:", size_attr);
	// 		ft_printf("%.*s]", size_attr, buf_attr);
	// 	}
	// 	else
	// 	{
	// 		ft_printf("%d:", size_attr);
	// 		break;
	// 	}
	// 	len += ft_strlen(buf_list + len);
	// }
}

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
