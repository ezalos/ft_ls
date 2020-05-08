/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:57:06 by ezalos            #+#    #+#             */
/*   Updated: 2020/05/08 22:20:22 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# define ARG_PROGRAM	1
# define ARG_OPTION		2
# define ARG_ARGUMENT	3
# define ARG_UNKNOWN	0

typedef	struct	s_one_arg
{
	const char	*name;
	char		**raw;
	int			len;
	const char	*help;
	//should be in the order they have been found
	//			from 0 elems to ac elems
	//can be :
	//			linked list
	//		->	pointer to first relevant av and relevant number ?
	char		**arg;
	int			arg_nb;
}				t_one_arg;

#define MAX_ARGS	10

typedef	struct	s_argp
{
	char		*prog;//av[0]
	char		*name;
	char		*help;
	int			ac;
	char		**av;
	char		*use;// which av have been treated ?
	//args DS should be:
	//					expandable
	//					able to retrieve from name quickly
	//	can be	->	red black tree
	//				Htable
	//				dynamic array
	t_one_arg	args[MAX_ARGS];
	int			nb_args;
	int			nb_opts;
}				t_argp;

#endif
