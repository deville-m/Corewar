/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:02:52 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/10 19:40:34 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "memory.h"
#include "ft_string.h"

static t_list	*parse_header(t_env *env)
{
	t_asm_token	*tok;
	t_list		*tmp;

	tmp = env->tok_head;
	tok = (t_asm_token *)tmp->content;
	while (tmp && tok->type <= STRING)
	{
		if (tok->type == COMMAND_NAME)
		{
			tmp = tmp->next;
			tok = (t_asm_token *)tmp->content;
			ft_memcpy(env->header->prog_name, tok->raw, ft_strlen(tok->raw));
		}
		else if (tok->type == COMMAND_COMMENT)
		{
			tmp = tmp->next;
			tok = (t_asm_token *)tmp->content;
			ft_memcpy(env->header->comment, tok->raw, ft_strlen(tok->raw));
		}
		tok = (t_asm_token *)tmp->content;
		tmp = tmp->next;
	}
	write(env->fd, env->header, sizeof(t_header));
	return (tmp);
}

static void		fill_label_gaps(t_env *env, int offset, t_list *haystack)
{
	t_list	*tmp;
	t_lab	*elem;
	t_lab	*needle;
	short	result;

	env->header->prog_size = offset;
	tmp = env->to_do;
	while (tmp)
	{
		needle = (t_lab *)tmp->content;
		haystack = env->lab_h;
		while (haystack)
		{
			elem = (t_lab *)haystack->content;
			if (ft_strcmp(elem->name, needle->name) == 0)
			{
				lseek(env->fd, needle->offset - offset, SEEK_END);
				result = (short)(elem->offset - needle->instr_offset);
				swap_endian(&(result), 2);
				write(env->fd, &result, 2);
			}
			haystack = haystack->next;
		}
		tmp = tmp->next;
	}
}

int				craft_file(t_env *env)
{
	int		last_offset;
	t_list	*ret;

	env->fd = create_output_file(env);
	ret = parse_header(env);
	last_offset = craft_prog(env, ret);
	fill_label_gaps(env, last_offset, NULL);
	if (lseek(env->fd, 0, SEEK_SET) == -1)
		bug_err("Error while last lseek for writing header\n");
	swap_endian(&(env->header->prog_size), 4);
	write(env->fd, env->header, sizeof(t_header));
	return (1);
}
