# include "head.h"

t_list			*ft_lstcut(t_list **alst, int indx)
{
	t_list	*search;
	t_list	*to_cut;
	int		i;

	i = 0;
	search = *alst;
	to_cut = *alst;
	if (indx == 0)
	{
		*alst = search->next;
		to_cut->next = NULL;
		return (to_cut);
	}
	if (search->next == NULL
		&& indx == -1)
		return (search);
	while (search != NULL
		&& search->next != NULL
		&& search->next->next != NULL
		&& (i + 1 < indx|| indx == -1))
	{
		search = search->next;
		i++;
	}
	to_cut = search->next;
	search->next = to_cut->next;
	to_cut->next = NULL;
	return (to_cut);
}
