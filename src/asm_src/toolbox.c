/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:50:37 by rbaraud           #+#    #+#             */
/*   Updated: 2018/06/04 20:03:27 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lst.h"
#include <stdlib.h>

void	bug_err(char *mess)
{
	ft_fprintf(2, "./asm: ");
	ft_fprintf(2, "%s", mess);
	perror("./asm");
	exit(EXIT_FAILURE);
}

/*
**	returns 0 if error, 1 otherwise.
**	Warning! This function doesn't create a copy of content, it just point
**  to it. In order to limit the number of malloc because it takes the line
**  already malloc by gnl.
*/

void	ft_lstinsert(t_list **head, void *content, int content_size)
{
	t_list	*new;

	if (!head || !content)
		bug_err("Error with t_list insert\n");
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		bug_err("Error with t_list insert\n");
	new->content = content;
	new->content_size = content_size;
	if (*head)
		new->next = *head;
	else
		new->next = NULL;
	*head = new;
}
