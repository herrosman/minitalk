/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:41:57 by aosman            #+#    #+#             */
/*   Updated: 2025/06/13 14:42:43 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		node = *lst;
		last = ft_lstlast(node);
		last->next = new;
	}
}
