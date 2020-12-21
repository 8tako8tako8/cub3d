/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:37:47 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/21 21:40:35 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_int_overflow(int sign, const char *str)
{
	int		digit;

	digit = 0;
	while (ft_isdigit(str[digit]))
		digit++;
	if (digit > 10)
		return (-1);
	if ((sign == 1 && ft_strncmp(str, "2147483647", 19) > 0)
		&& digit == 10)
		return (-1);
	if ((sign == -1 && ft_strncmp(str, "2147483648", 19) > 0)
		&& digit == 10)
		return (-1);
	return (1);
}

int		ft_atoi_ex(const char *str)
{
	long long		number;
	int				sign;
	int				i;

	number = 0;
	sign = 1;
	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (check_int_overflow(sign, str + i) == -1)
		return (check_int_overflow(sign, str + i));
	while (ft_isdigit(str[i]))
	{
		number = number * 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}

int		ft_strchr_ex(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return (1);
	return (0);
}

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

t_sprlst		*ft_lstlast_ex(t_sprlst *lst)
{
	t_sprlst	*curr_list;

	if (lst == NULL)
		return (NULL);
	curr_list = lst;
	while (curr_list->next != NULL)
		curr_list = curr_list->next;
	return (curr_list);
}

void	ft_lstadd_back_ex(t_sprlst **lst, t_sprlst *new)
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