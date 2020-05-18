/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:19:42 by ezalos            #+#    #+#             */
/*   Updated: 2020/05/18 20:05:25 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_struct_dirent_d_type(struct dirent *dir)
{
	ft_printf("%d ", dir->d_type);
	if (dir->d_type == DT_BLK)
		ft_printf("{Block device}");
	else if (dir->d_type == DT_CHR)
		ft_printf("{Character device}");
	else if (dir->d_type == DT_DIR)
		ft_printf("{Directory}");
	else if (dir->d_type == DT_FIFO)
		ft_printf("{Named pipe}");
	else if (dir->d_type == DT_LNK)
		ft_printf("{Symbolic Link}");
	else if (dir->d_type == DT_REG)
		ft_printf("{Regular file}");
	else if (dir->d_type == DT_SOCK)
		ft_printf("{UNIX Domain socket}");
	else if (dir->d_type == DT_UNKNOWN)
		ft_printf("{Unknown}");
	ft_printf(" ");
}

void	print_struct_dirent(struct dirent *dir)
{
	//if (_DIRENT_HAVE_D_NAMLEN)
	//	ft_printf("%-8d length of string in d_name\n", dir->d_namlen);
	//else
	ft_printf("[%3d]", ft_strlen(dir->d_name));
	ft_printf("\"%-15s\" ", dir->d_name);
	ft_printf("#%-8d ", dir->d_ino);
	ft_printf("%3dlen ", dir->d_reclen);
	print_struct_dirent_d_type(dir);
	ft_printf("\n");
}

void	print_struct_stat(struct stat *stat)
{
	ft_printf("%s %d\n", "/* ID of device containing file */", stat->st_dev);
	ft_printf("%s %d\n", "/* Inode number */", stat->st_ino);
	ft_printf("%s %d\n", "/* File type and mode */", stat->st_mode);
	ft_printf("%s %d\n", "/* Number of hard links */", stat->st_nlink);
	ft_printf("%s %d\n", "/* User ID of owner */", stat->st_uid);
	ft_printf("%s %d\n", "/* Group ID of owner */", stat->st_gid);
	ft_printf("%s %d\n", "/* Device ID (if special file) */", stat->st_rdev);
	ft_printf("%s %d\n", "/* Total size, in bytes */", stat->st_size);
	ft_printf("%s %d\n", "/* Block size for filesystem I/O */", stat->st_blksize);
	ft_printf("%s %d\n", "/* Number of 512B blocks allocated */", stat->st_blocks);
	ft_printf("%s %d\n", "/* Time of last access */", stat->st_atim);
	ft_printf("%s %d\n", "/* Time of last modification */", stat->st_mtim);
	ft_printf("%s %d\n", "/* Time of last status change */", stat->st_ctim);
	ft_printf("\n");
}

#define MAGIC_NUMBER_LEN		4
#define MAGIC_NUMBER_ELF		0x464c457f

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
		ft_printf("F");//FIFO/pipe
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
   S_ISUID     04000   set-user-ID bit
   S_ISGID     02000   set-group-ID bit (see below)
   S_ISVTX     01000   sticky bit (see below)

   S_IRWXU     00700   owner has read, write, and execute permission
   S_IRUSR     00400   owner has read permission
   S_IWUSR     00200   owner has write permission
   S_IXUSR     00100   owner has execute permission

   S_IRWXG     00070   group has read, write, and execute permission
   S_IRGRP     00040   group has read permission
   S_IWGRP     00020   group has write permission
   S_IXGRP     00010   group has execute permission

   S_IRWXO     00007   others (not in group) have read, write, and execute
   permission
   S_IROTH     00004   others have read permission
   S_IWOTH     00002   others have write permission
   S_IXOTH     00001   others have execute permission
   */

void	print_file_mode(struct stat sb)
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
			ft_printf("x");
		else
			ft_printf("-");
	}
	ft_printf(" ");
}

#include <pwd.h>

void	print_file_ownership(struct stat sb)
{
	struct passwd *pw;

	pw = getpwuid(sb.st_uid);
	ft_printf("%s ", pw->pw_name);
	pw = getpwuid(sb.st_gid);
	ft_printf("%s ", pw->pw_name);
}

void	print_file_size(size_t file_size)
{
	long long	size;
	float		save;
	int			shift;
	int			unit;

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
	ft_printf(" ");
}

void	print_file_link_count(struct stat sb)
{
	int			shift;

	shift = 2;
	ft_printf("%*ld ", shift, (long) sb.st_nlink);
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
	i = -1;
	while (time_dic && time_dic[++i])
	{
		if (i == 1)
			ft_printf("%s ", time_dic[i]);
		if (i == 2)
			ft_printf("%2s ", time_dic[i]);
		if (i == 3)
			ft_printf("%.5s ", time_dic[i]);
	}
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

	if (parse_get("Recurse"))
		if (file->check == IS_CURRENT_DIR || file->check == IS_UP_DIR)
			return (0);
	print_file_color(file->statbuf, file->path);
	print_file_type(file->statbuf);
	ft_printf("%~{}");
	print_file_mode(file->statbuf);
	print_file_link_count(file->statbuf);
	print_file_ownership(file->statbuf);
	print_file_size(file->statbuf.st_size);
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
	size_t	sum = tree_inorder(node, &tree_sum_size_inorder);

	if (parse_get("-R"))
	{
		if (((t_sys_files*)node->content)->parent->parent)
			ft_printf("\n");
		ft_printf("%s\n", ((t_sys_files*)node->content)->parent->path);
	}
	ft_printf("total ");
	print_file_size(sum);
	ft_printf("\n");
	tree_inorder(node, &print_ls);
}
