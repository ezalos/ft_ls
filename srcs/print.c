/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:19:42 by ezalos            #+#    #+#             */
/*   Updated: 2020/09/25 18:53:25 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define		FORMAT_RIGHTS		0
#define		FORMAT_F_LINK		1
#define		FORMAT_U_NAME		2
#define		FORMAT_G_NAME		3
#define		FORMAT_F_SIZE		4
#define		FORMAT_T_HOUR		5
#define		FORMAT_T_YEAR		6


int			get_format(t_ls_format *new_format, int field)
{
	static t_ls_format	*format;
	int					value;

	if (new_format)
		format = new_format;
	value = 0;
	if (format)
		value = ((int*)format)[field];
	return (value);
}

uint32_t	read_magic_number(char *path)
{
	char			magic_number[4] = ".ELF";
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		ft_bzero(magic_number, 4);
		read(fd, (char*)magic_number, MAGIC_NUMBER_LEN);
		close(fd);//does it can fail ?
	}
	return (*(uint32_t*)magic_number);
}

void	print_file_color(struct stat sb, char *path)
{
	uint32_t file_type;

	if (S_IFBLK == (sb.st_mode & S_IFMT))		//block device
		ft_printf("%~{150;255;255}");
	else if (S_IFCHR == (sb.st_mode & S_IFMT))	// character device
		ft_printf("%~{255;150;255}");
	else if (S_IFDIR == (sb.st_mode & S_IFMT))	//directory
		ft_printf("%~{255;255;150}");
	else if (S_IFIFO == (sb.st_mode & S_IFMT))	//FIFO pipe
		ft_printf("%~{150;150;255}");
	else if (S_IFLNK == (sb.st_mode & S_IFMT))	//symlink
		ft_printf("%~{255;150;150}");
	else if (S_IFREG == (sb.st_mode & S_IFMT))	//regular file
	{
		file_type = read_magic_number(path);
		if (file_type == MAGIC_NUMBER_ELF)
			ft_printf("%~{220;125;255}");
		else
			ft_printf("%~{}");

	}
	else if (S_IFSOCK == (sb.st_mode & S_IFMT))	//socket
		ft_printf("%~{255;150;255}");
	else											//unknown
		ft_printf("%~{255;255;150}");
}


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

/*
**   S_ISUID     04000   set-user-ID bit
**   S_ISGID     02000   set-group-ID bit (see below)
**   S_ISVTX     01000   sticky bit (see below)
**
**   S_IRWXU     00700   owner has read, write, and execute permission
**   S_IRUSR     00400   owner has read permission
**   S_IWUSR     00200   owner has write permission
**   S_IXUSR     00100   owner has execute permission
**
**   S_IRWXG     00070   group has read, write, and execute permission
**   S_IRGRP     00040   group has read permission
**   S_IWGRP     00020   group has write permission
**   S_IXGRP     00010   group has execute permission
**
**   S_IRWXO     00007   others (not in group) have read, write, and execute
**   permission
**   S_IROTH     00004   others have read permission
**   S_IWOTH     00002   others have write permission
**   S_IXOTH     00001   others have execute permission
*/

#include <sys/xattr.h>

int		extended_attr(t_sys_files *file)
{
	char		buf_list[1000];
	char		buf_attr[1000];
	ssize_t		size_list;
	ssize_t		size_attr;
	int			len;

	ft_bzero(buf_list, 1000);
	size_list = llistxattr(file->path, buf_list, 1000);
	if (size_list)
		return (1);
	return (0);
	ft_printf("List size: %d", size_list);
	len = 0;
	while (len < (int)size_list)
	{
		ft_bzero(buf_attr, 1000);
		if ((size_attr = lgetxattr(file->path, buf_list + len, buf_attr, 1000)) > 0)
		{
			buf_attr[size_attr] = '\0';
			ft_printf("[%s:", buf_list + len);
			ft_printf("%d:", size_attr);
			ft_printf("%.*s]", size_attr, buf_attr);
		}
		else
		{
			ft_printf("%d:", size_attr);
			break;
		}
		len += ft_strlen(buf_list + len);
	}
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
		if (1 & (mode >> i))
		{
			if (i == 6 && mode & S_ISUID)
				ft_printf("s");
			else if (i == 3 && mode & S_ISGID)
				ft_printf("s");
			else
				ft_printf("x");
		}
		else
		{
			if (i == 0 && mode & S_ISVTX)
				ft_printf("T");
			else if (i == 6 && mode & S_ISUID)
				ft_printf("S");
			else if (i == 3 && mode & S_ISGID)
				ft_printf("S");
			else
				ft_printf("-");
		}
	}
	if (extended_attr(file))
		ft_printf("+");
	else if (get_format(NULL, FORMAT_RIGHTS))
		ft_printf(" ");
	ft_printf(" ");
}


void	print_file_ownership(struct stat sb)
{
	struct passwd	*pw;
	struct group	*grp;

	pw = getpwuid(sb.st_uid);
	if (pw)
		ft_printf("%-*s ", get_format(NULL, FORMAT_RIGHTS), pw->pw_name);
	else
		ft_printf("~%-*lld ", get_format(NULL, FORMAT_RIGHTS) - 1, sb.st_uid);
	grp = getgrgid(sb.st_gid);
	if (grp)
		ft_printf("%-*s ", get_format(NULL, FORMAT_RIGHTS), grp->gr_name);
	else
		ft_printf("~%-*lld ", get_format(NULL, FORMAT_RIGHTS) - 1, sb.st_gid);
}

void	print_file_size(size_t file_size)
{
	long long	size;
	float		save;
	int			shift;
	int			unit;

	ft_printf("%*u", get_format(NULL, FORMAT_F_SIZE), file_size);
	return ;
	size = 1;
	unit = 1024;
	save = file_size;
	shift = 3;
	while (save > unit)
	{
		save = save / unit;
		size++;
	}
	//ft_printf("");
	if (size == 1)
	{
		ft_printf("%*.*f", shift + 1, 0, save);
	}
	else
	{
		if (save < 10)
			ft_printf("%*.*f", shift, 1, save);
		else
			ft_printf("%*.*f", shift, 0, save);
		if (size == 2)
			ft_printf("K");
		else if (size == 3)
			ft_printf("M");
		else if (size == 4)
			ft_printf("G");
		else if (size == 2)
			ft_printf("T");
	}
}

void	print_file_link_count(struct stat sb)
{
	int			shift;

	shift = get_format(NULL, FORMAT_F_LINK);
	ft_printf("%*ld ", shift, (long) sb.st_nlink);
}

#define TIMESTR_MON		1
#define TIMESTR_DAY		2
#define TIMESTR_HOU		3
#define TIMESTR_YEA		4

int		check_file_time(time_t file_time)
{
	static time_t	now;

	if (!now)
		now = time(NULL);
	if (file_time > now + 3600)
		return (TRUE);
	if ((unsigned long long)file_time < (unsigned long long)now - 15552000)//1616544000)
		return (TRUE);
	return (FALSE);

}

void	print_file_last_modif(struct stat sb)
{
	char	*no_newline;
	char	**time_dic;
	int		i;

	no_newline = ctime(&sb.st_mtime);
	i = -1;
	while (no_newline[++i])
		if (no_newline[i] == '\n')
			no_newline[i] = ' ';
	time_dic = ft_strsplit(no_newline, ' ');
	ft_printf("%-5s ", time_dic[TIMESTR_MON]);
	ft_printf("%2s ", time_dic[TIMESTR_DAY]);
	if (check_file_time(sb.st_mtime) || time_dic[TIMESTR_YEA][0] != '2')
	{
		//no need for lonely file
		//if (get_format(NULL, FORMAT_T_HOUR))
		//	ft_printf(" ");
		ft_printf(" %04s ", time_dic[TIMESTR_YEA]);
	}
	else
		ft_printf("%.5s ", time_dic[TIMESTR_HOU]);
	//ft_printf("%llu-", (unsigned long long)time(NULL));
	//ft_printf("%llu=", (unsigned long long)sb.st_mtime);
	//ft_printf("%lld ", (unsigned long long)time(NULL) - (unsigned long long)sb.st_mtime);
}

void	print_file_name(char *name)
{
	ft_printf("%s", name);
}

void	print_file_link(t_sys_files *file)
{
	struct stat		stat_link;
	char			*buf;
	size_t			bufsiz = 500;

	if (S_IFLNK == (file->statbuf.st_mode & S_IFMT))
	{
		if (stat(file->path, &stat_link) != 0 /*SUCCESS*/)
		{
			perror(ERROR_DIR_STAT);
			return ;
		}
		buf = ft_memalloc(bufsiz);
		if (readlink(file->path, buf, bufsiz) == -1)
			return ;
		ft_printf(" -> ");
		print_file_color(stat_link, buf);
		print_file_name(buf);
		ft_printf("%~{}");
	}
}

int		print_ls(t_rbt *node)
{
	t_sys_files *file = node->content;

	if (parse_get("recursive"))
		if (file->check == IS_CURRENT_DIR || file->check == IS_UP_DIR)
			return (0);
	print_file_color(file->statbuf, file->path);
	print_file_name(file->d_name);
	ft_printf("%~{}");
	ft_printf("  ");
	return (0);
}
int		print_ls_l(t_rbt *node)
{
	t_sys_files *file = node->content;


	if (parse_get("recursive"))
		if (file->check == IS_CURRENT_DIR || file->check == IS_UP_DIR)
			return (0);
	print_file_color(file->statbuf, file->path);
	print_file_type(file->statbuf);
	ft_printf("%~{}");
	print_file_mode(file->statbuf, file);
	print_file_link_count(file->statbuf);
	print_file_ownership(file->statbuf);
	print_file_size(file->statbuf.st_size);
	ft_printf(" ");
	print_file_last_modif(file->statbuf);
	print_file_color(file->statbuf, file->path);
	print_file_name(file->d_name);
	ft_printf("%~{}");
	print_file_link(file);
	ft_printf("\n");
	return (0);
}

int			tree_sum_size_inorder(t_rbt *root)
{
	int		value = 0;

	if (root != NULL)
		value += ((t_sys_files*)root->content)->statbuf.st_size;
	return value;
}

void	ls_output(t_rbt *node)
{
	t_sys_files	*file;
	size_t	sum = tree_inorder(node, &tree_sum_size_inorder);

	file = node->content;
	if (parse_get("recursive"))
	{
		if (file->parent)
		{
			if (file->parent->parent)
				ft_printf("\n");
			ft_printf("%s\n", ((t_sys_files*)node->content)->parent->path);
		}
	}
	if (file->parent)
		get_format(&file->parent->format, 0);
	if (parse_get("list"))//TODO: if more than one file
	{
		ft_printf("total ");
		print_file_size(sum);
		ft_printf("\n");
	}
	if (!parse_get("reverse"))
		tree_inorder(node, parse_get("list") ? &print_ls_l : &print_ls);
	else
		tree_inrorder(node, parse_get("list") ? &print_ls_l : &print_ls);
	parse_get("list") ? ft_printf("") : ft_printf("\n");
}
