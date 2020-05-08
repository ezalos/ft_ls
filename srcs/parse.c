/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 13:22:18 by ezalos            #+#    #+#             */
/*   Updated: 2020/05/08 22:20:51 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_argp	*arg_mem(void)
{
	static t_argp	args;

	return (&args);
}

void	arg_print_one(t_one_arg *arg)
{
	int		i;
	ft_printf("\tname:    %s\n", arg->name);
	ft_printf("\thelp:    %s\n", arg->help);
	ft_printf("\targ nb:  %d\n", arg->arg_nb);
	ft_printf("\traw :    %p\n", arg->raw);
	ft_printf("\n\traw len: %d\n", arg->len);
	ft_printf("\targs:    ");
	i = -1;
	while (++i < arg->len)
		ft_printf("%s ", arg->raw[i]);
	ft_printf("\n");
}

void	arg_print(void)
{
	t_argp	*arg;
	int		i;
	
	arg = arg_mem();
	ft_printf("prog:   %s\n", arg->prog);
	ft_printf("name:   %s\n", arg->name);
	ft_printf("help:   %s\n", arg->help);
	ft_printf("ac:     %d\n", arg->ac);
	ft_printf("nb_arg: %d\n", arg->nb_args);
	ft_printf("use:\n\t");
	i = -1;
	while (++i < arg->ac)
		ft_printf("%d %s\t", arg->use[i], arg->av[i]);
	ft_printf("\n");
	i = -1;
	while (++i < arg->nb_args)
	{
		ft_printf("\nARG %d\n", i);
		arg_print_one(&arg->args[i]);
	}
}

int		arg_add(char *name, char *help)
{
	t_argp	*arg;

	arg = arg_mem();
	if (arg->nb_args < MAX_ARGS)
	{
		arg->args[arg->nb_args].name = name;
		arg->args[arg->nb_args].help = help;
		arg->args[arg->nb_args].arg_nb = arg->nb_args;
		arg->nb_args++;
	}
	return (arg->nb_args);
}

t_argp	*arg_new(char *name, char *help)
{
	t_argp	*arg;
	arg = arg_mem();

	ft_bzero(arg, sizeof(t_argp));
	arg->name = name;
	arg->help = help;
	return (arg);
}

int		arg_parse(int ac, char **av)
{
	int		i;
	int		j;
	t_argp	*arg;

	arg = arg_mem();
	i = 0;
	arg->ac = ac;
	arg->av = av;
	arg->use = ft_memalloc(ac + 1);
	arg->prog = av[i];
	arg->use[i] = ARG_PROGRAM;
	while (++i < ac)
	{
		j = -1;
		while (++j < arg->nb_args)
		{
			if (!ft_strcmp(av[i], arg->args[j].name))
			{
				arg->args[j].raw = &av[i];
				arg->args[j].arg = &av[i];
				arg->args[j].len = ac - i;
				arg->args[j].len = 1;
				arg->use[i] = ARG_OPTION;
				arg->nb_opts++;
			}
		}
	}
	return (0);
}

t_one_arg	*arg_get(char *name)
{
	int		i;
	t_argp	*arg;

	arg = arg_mem();
	i = -1;
	if (!name)
	{
		while (++i < arg->nb_args)
			if (arg->use[i] == ARG_UNKNOWN)
				return (&arg->args[arg->nb_args - 1]);// bad way
		return (NULL);
	}

	while (++i < arg->nb_args)
		if (!ft_strcmp(name, arg->args[i].name))
		{
			if (arg->args[i].raw)
				return (&arg->args[i]);
		}
	return (NULL);
}

int		arg_usage(void)
{
	int		i;
	t_argp	*arg;

	arg = arg_mem();
	ft_printf("Usage: ");
	ft_printf("%s ", arg->prog);
	i = -1;
	while (++i < arg->nb_args)
		ft_printf("[%s] ", arg->args[i].name);
	ft_printf("\n\n");
	ft_printf("%s:\n\t%s\n\n", arg->name, arg->help);
	ft_printf("Options:\n");
	i = -1;
	while (++i < arg->nb_args)
		ft_printf("\t%s \t%s\n", arg->args[i].name, arg->args[i].help);
	ft_printf("\n");
	return (0);
}

