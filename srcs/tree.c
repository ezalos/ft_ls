/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:29:49 by ezalos            #+#    #+#             */
/*   Updated: 2020/05/03 21:10:33 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


/*
 *	Memory management
 */

t_rbt		*tree_new_node(void *content)
{
	t_rbt		*node;

	node = ft_memalloc(sizeof(t_rbt));
	node->content = content;
	node->color = RED;
	return (content);
}



/*
 *	Genealogy
 */


t_rbt		*tree_parent(t_rbt *node)
{
	if (node)
		return (node->parent);
	//DEBUG_ERROR_PRINT("Node sent is NULL, or doesnt have dad");
	return (NULL);
}

t_rbt		*tree_root(t_rbt *node)
{
	t_rbt	*up;

	up = tree_parent(node);
	while (up != NULL)
	{
//		ft_printf("n: %p\n", node);
		node = up;
		up = tree_parent(node);
	}
	return (node);
}


t_rbt		*tree_sibling(t_rbt *node)
{
	if (node && node->parent)
	{
		if (node == node->parent->left)
		{
			return (node->parent->right);
		}
		else
		{
			return (node->parent->left);
		}
	}
	//DEBUG_ERROR_PRINT("");
	return (NULL);
}

t_rbt		*tree_uncle(t_rbt *node)
{
	return ((tree_sibling(tree_parent(node))));
}


/*
 *	Rotations
 */

void	tree_rot_left(t_rbt *node)
{
	t_rbt* son_right = node->right;
	t_rbt* parent = tree_parent(node);

	// Since the leaves of a red-black tree are empty,
	// they cannot become internal nodes.
	if(son_right == NULL)
		return ;

	node->right = son_right->left;
	son_right->left = node;
	node->parent = son_right;

	// Handle other child/parent pointers.
	if (node->right != NULL)
		node->right->parent = node;

	// Initially node could be the root.
	if (parent != NULL)
	{
		if (node == parent->left)
			parent->left = son_right;
		else if (node == parent->right)
			parent->right = son_right;
	}
	son_right->parent = parent;
}

void	tree_rot_right(t_rbt *node)
{
	t_rbt* son_left = node->left;
	t_rbt* parent = tree_parent(node);

	// Since the leaves of a red-black tree are empty,
	// they cannot become internal nodes.
	if(son_left == NULL)
		return ;

	node->left = son_left->right;
	son_left->right = node;
	node->parent = son_left;

	// Handle other child/parent pointers.
	if (node->left != NULL)
		node->left->parent = node;

	// Initially node could be the root.
	if (parent != NULL)
	{
		if (node == parent->left)
			parent->left = son_left;
		else if (node == parent->right)
			parent->right = son_left;
	}
	son_left->parent = parent;
}

/*
 * 	Recoloration
 */

void		tree_recoloring(t_rbt *node)
{
	if (node->parent == NULL)
		node->color = BLACK;
	else if (node->parent->color != BLACK)
	{
		if (tree_uncle(node)->color == RED)
		{
			node->parent->color = BLACK;
			tree_uncle(node)->color = BLACK;

		}
	}
}

/*
 * 	Tree expansion / deletion
 */

void		tree_insert_recurse(t_rbt *root, t_rbt *n)
{
	DEBUG_FUNC;
	tree_inorder(root);
	tree_inorder(n);
	// Recursively descend the tree until a leaf is found.
	if (root != NULL)
	{
		if (n->key < root->key)
		{
			if (root->left != NULL)
			{
				tree_insert_recurse(root->left, n);
				return;
			}
			else
			{
				root->left = n;
			}
		}
		else
		{ // n->key >= root->key
			if (root->right != NULL)
			{
				tree_insert_recurse(root->right, n);
				return;
			}
			else
			{
				ft_printf("add\n");
				root->right = n;
			}
		}
	}

	// Insert new Node n.
	n->parent = root;
	n->left = NULL;
	n->right = NULL;
	n->color = RED;
}

void		tree_insert_case_1(t_rbt *n)
{
	DEBUG_FUNC;
	n->color = BLACK;
}

void		tree_insert_case_2(t_rbt *n)
{
	DEBUG_FUNC;
	// Do nothing since tree is still valid.
	(void)n;
	return;
}

void		tree_insert_case_3(t_rbt *n)
{
	DEBUG_FUNC;
	tree_parent(n)->color = BLACK;
	tree_uncle(n)->color = BLACK;
	tree_parent(tree_parent(n))->color = RED;
	tree_insert_repair(tree_parent(tree_parent(n)));
}

void		tree_insert_case_4(t_rbt *n)
{
	DEBUG_FUNC;
	t_rbt *p = tree_parent(n);
	t_rbt *g = tree_parent(p);

	if (n == p->right && p == g->left)
	{
		tree_rot_left(p);
		n = n->left;
	} 
	else if (n == p->left && p == g->right) 
	{
		tree_rot_right(p);
		n = n->right;
	}

	if (n == p->left)
	{
		tree_rot_right(g);
	} 
	else
	{
		tree_rot_left(g);
	}
	p->color = BLACK;
	g->color = RED;
}

void		tree_insert_repair(t_rbt *n)
{
	DEBUG_FUNC;
	if (tree_parent(n) == NULL)
	{
		tree_insert_case_1(n);
	}
	else if (tree_parent(n)->color == BLACK)
	{
		tree_insert_case_2(n);
	}
	else if (tree_uncle(n) != NULL && tree_uncle(n)->color == RED)
	{
		tree_insert_case_3(n);
	}
	else
	{
		tree_insert_case_4(n);
	}
}

t_rbt		*tree_insert(t_rbt *root, void* content, int key)
{
	DEBUG_FUNC;
	t_rbt	*n = tree_new_node(content);
	n->key = key;
	// Insert new Node into the current tree.
	//tree_inorder(n);
	tree_insert_recurse(root, n);
		ft_printf("Insert\n");
		tree_inorder(root);
		tree_inorder(n);

	// Repair the tree in case any of the red-black properties have been violated.
	tree_insert_repair(n);
		ft_printf("Repair\n");
		tree_inorder(root);
		tree_inorder(n);

	// Find the new root to return.
		ft_printf("loop\n");
	root = tree_root(n);
		ft_printf("no loop\n");
	return root;
}

/*
 *	Search
 */


/*
 *	Print
 */

void		tree_str(t_rbt *root)
{
	if (root != NULL)
	{
		if (root->color == RED)
			ft_printf("R%~{255;150;150}%d%~{}", root->key);
		else
			ft_printf("B%~{150;150;255}%d%~{}", root->key);
	}
	else
		ft_printf("null");
}

void		tree_inorder(t_rbt *root) 
{
	if (root != NULL) 
	{
		tree_inorder(root->left);
		ft_printf("P "); 
 		tree_str(root->parent);
		ft_printf("\t"); 
 		tree_str(root);
		ft_printf("\tl "); 
 		tree_str(root->left);
		ft_printf("\tr "); 
 		tree_str(root->right);
		ft_printf("\n"); 
		tree_inorder(root->right); 									    
	}
}

#define NB_OF_SPACE		5

void	padding_before(t_rbt *node, size_t space)
{
	t_rbt	*parent;
	size_t 		i;

	i = 0;
	parent = tree_parent(node);
	while (i < space)
	{
		printf(" ");
		i++;
	}
	if (parent != NULL)
		(parent->left == node) ? printf("╰─ ") : printf("╭─ ");
}

void	padding_after(t_rbt *node)
{
	size_t 		i;
	size_t		padding;

	if (node->left != NULL || node->right != NULL)
	{
		padding = NB_OF_SPACE - ft_nb_len(node->key, 10) - 4;
		i = 0;
		while (i < padding)
		{
			printf("─");
			i++;
		}
		if (tree_root(node) == node)
			printf("───");
		printf("┤");
	}
	printf("\n");
}

void	tree_print(t_rbt *node, size_t deep)
{
	DEBUG_FUNC;
	if (node == NULL)
		return ;
	tree_print(node->right, deep + 1);

	padding_before(node, (deep * NB_OF_SPACE));
	if (node->color == RED)
		printf("\033[0;31m%d \033[00m", node->key);
	else
		printf("\033[37m%d \033[00m", node->key);
	padding_after(node);

	tree_print(node->left, deep + 1);
}

