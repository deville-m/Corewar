/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:50:37 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/10 18:32:05 by rbaraud          ###   ########.fr       */
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

void	create_token(t_env *env, enum e_type type, int line, int column, char *raw, int data, int option)
{
	t_asm_token	*new;

	if (!raw)
		bug_err("Error while creating token, no raw info\n");
	if (!(new = (t_asm_token *)malloc(sizeof(t_asm_token))))
		bug_err("Error while creating token, can't malloc element\n");
	new->type = type;
	new->line = line;
	new->column = column;
	new->raw = raw;
	new->data = data;
	new->option = option;
	ft_lstinsert(&(env->tok_head), (void *)(new), sizeof(new));
}

void	swap_endian(void *data, size_t size)
{
	char    tmpdata;
	char    *tmp;
	size_t  i;

	if (!data)
		return ;
	tmp = (char *)data;
	i = 0;
	--size;
	while (i < size)
	{
		tmpdata = tmp[i];
		tmp[i] = tmp[size];
		tmp[size] = tmpdata;
		++i;
		--size;
	}
}
