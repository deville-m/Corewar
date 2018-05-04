/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_assembler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:22:01 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/04 13:31:28 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "lst.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*
** temporary funciton, waiting for Clement error functions.
*/

void	bug_err(char *mess)
{
	perror(mess);
	exit(0);
}

/*
**	returns 0 if error, 1 otherwise.
**	Warning! This function doesn't create a copy of content, it just point
**  to it. In order to limit the number of malloc because it takes the line
**  already malloc by gnl.
*/

int		ft_lstinsert(t_list **head, void *content, int content_size)
{
	t_list	*new;

	if (!head)
		return (0);
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (0);
	new->content = content;
	new->content_size = content_size;
	if (*head)
		new->next = *head;
	else
		new->next = NULL;
	*head = new;
	return (1);
}

void	tmp_print_lst(t_list *head)
{
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

void	stupid_asm(char *in_name)
{
	int		ret;
	int		fd;
	t_list	*head;
	char	*line;

	if (!(fd = open(in_name, O_RDONLY)))
		bug_err("Error while opening file");

	head = NULL;
	while ((ret = get_next_line(fd, &line)) != 0)
	{
		if (ret == -1)
			bug_err("gnl error while reading file");
		ft_lstinsert(&head, (void *)line, (int)ft_strlen(line) + 1);
	}
	ft_lstreverse(&head);

	tmp_print_lst(head);

	if (close(fd) == -1)
		bug_err("Error while closing file");
}
