/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:45 by ldevelle          #+#    #+#             */
/*   Updated: 2020/09/30 22:12:03 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	init_options_and_arguments(void)
{
	parse_new("ls", PROGRAME_DESCRIPTION);
	parse_add_option('R', "recursive", "Recursively visit each directory");
	parse_add_option('r', "reverse", "Reverse sort order");
	parse_add_option('l', "list", "List file information");
	parse_add_option('a', "all", "Show hidden files");
	parse_add_option('t', "time", "Sort files by time");
	parse_add_option('s', "human-size", "Display sizes with units");
	parse_add_option('g', "game", "Launch a game of snake ;)");
	parse_add_option('h', "help", "Display Usage (this message)");
	parse_add_arg("PATH", "List sorted information about the content of the \
directory. Default PATH is current directory.");
}

void	ls_multi_path(int ac, char**av)
{
	t_sys_files	*file;
	int			i;

	(void)ac;
	file = NULL;
	if (parse_get("PATH") == NULL)
	{
		file = file_struct(DEFAULT_ARGUMENT, NULL);
		if (file)
			one_level(file);
	}
	else
	{
		i = parse_get("PATH")->arg_place;
		while (i < ac)
		{
			if (i > parse_get("PATH")->arg_place)
				ft_printf("\n");
			file = file_struct(av[i], NULL);
			if (file)
				one_level(file);
			i++;
		}
	}
	// free_file_struct((void**)&file);
}

int		main(int ac, char **av)
{
	*(switch_garbage()) = FALSE;
	init_options_and_arguments();
	if (parse_args(ac, av) == FAILURE)
		return (0);
	if (parse_get("help") != NULL)
		return (parse_usage());
	else if (parse_get("game"))
		return (snake());
	ls_multi_path(ac, av);
	parse_free();
	return (0);
}
