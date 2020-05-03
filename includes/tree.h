/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:51:38 by ezalos            #+#    #+#             */
/*   Updated: 2020/05/03 19:01:25 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

enum	e_color { BLACK, RED  };

typedef struct		s_rbt
{
	struct s_rbt	*parent;
	struct s_rbt	*left;
	struct s_rbt	*right;

	void			*content;
	int				key;
	enum e_color	color;
}					t_rbt;

typedef	int		(t_rbt_compare)(void *, void *);

#endif