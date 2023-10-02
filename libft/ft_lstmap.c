/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:03:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/02 21:29:32 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		temp = malloc(sizeof(t_list));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		temp->paths = (*f)(lst->paths);
		temp->next = NULL;
		if (!new)
			new = temp;
		else
			ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
