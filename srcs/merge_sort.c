/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:21:37 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 02:06:45 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_cmp_distance_to_spr(t_sprlst *list1, t_sprlst *list2, 
                                                    double pos_x, double pos_y)
{
	double		distance1;
	double		distance2;

	distance1 = ((pos_x - list1->x) * (pos_x - list1->x) 
                                    + (pos_y - list1->y) * (pos_y - list1->y));
	distance2 = ((pos_x - list2->x) * (pos_x - list2->x) 
                                    + (pos_y - list2->y) * (pos_y - list2->y));
	if (distance1 >= distance2)
		return (1);
	else
		return (0);
}

t_sprlst	*ft_merge_lst(t_sprlst *list1, t_sprlst *list2, 
                                                    double pos_x, double pos_y)
{
    t_sprlst  *newlst_end;
    t_sprlst  newlst_head;

    newlst_end = &newlst_head;
    while ((list1 != NULL) && (list2 != NULL))
    {
        if (ft_cmp_distance_to_spr(list1, list2, pos_x, pos_y))
        {
            newlst_end->next = list1;
            list1 = list1->next;
            newlst_end = newlst_end->next;
        }
        else
        {
            newlst_end->next = list2;
            list2 = list2->next;
            newlst_end = newlst_end->next;
        }
    }
    if (list1 == NULL)
        newlst_end->next = list2;
    else
        newlst_end->next = list1;
    return (newlst_head.next);
}

t_sprlst  *ft_lst_merge_sort(t_sprlst *list, double pos_x, double pos_y)
{
    t_sprlst      *front;
    t_sprlst      *back;
    t_sprlst      *sepa;

    // 要素が１つ以下なら終了
    if (list == NULL || list->next == NULL)
        return (list);
    // リストの中心を探す。1:2でポインタを動かす。
    front = list;
    back = list->next;
	if (back != NULL)
		back = back->next;
    while (back != NULL)
    {
        front = front->next;
        back = back->next;
        if (back != NULL)
            back = back->next;
    }
    sepa = front->next;
    front->next = NULL;
    return (ft_merge_lst(ft_lst_merge_sort(list, pos_x, pos_y), 
                        ft_lst_merge_sort(sepa, pos_x, pos_y), pos_x, pos_y));
}