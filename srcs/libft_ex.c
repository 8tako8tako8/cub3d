/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:37:47 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 16:13:39 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_lstclear_ex(t_sprlst **lst)
{
	t_sprlst	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if (*lst)
			free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_sprlst	*ft_newspr(double x, double y)
{
	t_sprlst	*newlist;

	if (!(newlist = (t_sprlst *)malloc(sizeof(t_sprlst))))
		return (NULL);
	newlist->x = x;
	newlist->y = y;
	newlist->next = NULL;
	return (newlist);
}

t_sprlst	*ft_lstlast_ex(t_sprlst *lst)
{
	t_sprlst	*curr_list;

	if (lst == NULL)
		return (NULL);
	curr_list = lst;
	while (curr_list->next != NULL)
		curr_list = curr_list->next;
	return (curr_list);
}

void		ft_lstadd_back_ex(t_sprlst **lst, t_sprlst *new)
{
	t_sprlst		*curr_lst;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_lst = ft_lstlast_ex(*lst);
	curr_lst->next = new;
}

int			ft_lstsize_ex(t_sprlst *lst)
{
	t_sprlst	*curr_lst;
	int			i;

	if (lst == NULL)
		return (0);
	curr_lst = lst;
	i = 1;
	while (curr_lst->next != NULL)
	{
		curr_lst = curr_lst->next;
		i++;
	}
	return (i);
}
