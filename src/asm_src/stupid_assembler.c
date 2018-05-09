/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_assembler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:22:01 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 18:17:32 by rbaraud          ###   ########.fr       */
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
	t_ltoken	*love_void;

	while (head)
	{
		love_void = (t_ltoken *)head->content;
		ft_printf("raw: >%s<\n", love_void->raw);
		head = head->next;
	}
}

int	create_token(t_env *env, enum e_type type, int line, int column, char *raw, int data)
{
	t_ltoken	*new;

	if (!raw)
		return (0);
	if (!(new = (t_ltoken *)malloc(sizeof(t_ltoken))))
		return (0);
	new->type = type;
	new->line = line;
	new->column = column;
	new->raw = raw;
	new->data = data;
//	new->data = ft_treat(new->type, new->raw);

	ft_lstinsert(&(env->tok_head), (void *)(new), sizeof(new));
	return (1);
}

char	*string_token(int fd)
{
	int		ret;
	char	buf;
	char	*result;
	int		offset;

	offset = 0;
	while ((ret = read(fd, &buf, 1)) != 0)
	{
		if (ret == -1)
			bug_err("Error while reading file"); //possible to use errno
		offset += ret;
		if (buf == '"')
		{
			offset += 1;
			if (!(result = (char *)malloc(sizeof(char) * (offset + 1))))
				return (NULL);
			ft_bzero(result, offset + 1);
			lseek(fd, -offset, SEEK_CUR); // warning return values
			read(fd, result, offset); // warning return values
			return (result); // tmp
		}
	}
	return (NULL);
}

char		ret_letter(int offset, char *haystack)
{
	if (offset > (int)ft_strlen(haystack))
		return ((char)-2);
	else
		return (haystack[offset]);
}

void		analyser(t_env *env, int fd, char buf)
{
	int		ret;

	ret = 1;
	if (buf == STRING_CHAR)
		ret = create_token(env, STRING, 4, 2, string_token(fd), -1);
	else if (buf == SEPARATOR_CHAR)
		ret = create_token(env, SEPARATOR, 4, 2, ft_strdup(","), -1);
	else if (buf == EOL)
		ret = create_token(env, ENDLINE, 4, 2, ft_strdup("\n"), -1);
	else if (buf == DIRECT_CHAR)
		ret = craft_directs(env, fd);
	else if (buf == COMMENT_CHAR)
		ret = oh_a_comment_pass_it(fd);

	if (ret == 0)
		bug_err("Error while creating token");
}

static void	reader(t_env *env, int fd, int offset)
{
	int		ret;
	char	buf;
//	int		len;

	while ((ret = read(fd, &buf, 1)) != 0)
	{
		if (ret == -1)
			bug_err("Error while reading file"); //possible to use errno
		offset += ret;
		analyser(env, fd, buf);
	}
}

void	stupid_asm(t_env *env, char *in_name)
{
	int		fd;

	if (!(fd = open(in_name, O_RDONLY)))
		bug_err("Error while opening file");

	reader(env, fd, 0);

	ft_lstreverse(&(env->tok_head));
	tmp_print_lst(env->tok_head);

	if (close(fd) == -1)
		bug_err("Error while closing file");
}
