/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:02:52 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/13 15:29:23 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "memory.h"
#include "ft_string.h"

static void		clean_copy_into(char *dst, t_list *elem)
{
	t_asm_token	*tok;
	char		*clean;

	tok = (t_asm_token *)elem->content;
	clean = ft_strtrimc(tok->raw, '"');
	ft_memcpy(dst, clean, ft_strlen(clean));
	free(clean);
}

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
			clean_copy_into(env->header->prog_name, tmp);
		}
		if (tok->type == COMMAND_COMMENT)
		{
			tmp = tmp->next;
			clean_copy_into(env->header->comment, tmp);
		}
		tmp = tmp->next;
		tok = (t_asm_token *)tmp->content;
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
//	int		found;

	env->header->prog_size = offset;
	tmp = env->to_do;
	while (tmp)
	{
//		found = 0;
		needle = (t_lab *)tmp->content;
		haystack = env->lab_h;
		while (haystack)
		{
			elem = (t_lab *)haystack->content;
			if (ft_strcmp(elem->name, needle->name) == 0)
			{
//				found = 1;
				lseek(env->fd, needle->offset - offset, SEEK_END);
				result = (short)(elem->offset - needle->instr_offset);
				swap_endian(&(result), 2);
				write(env->fd, &result, 2);
			}
			haystack = haystack->next;
		}
//		found ? bug_err("Called label doesn't exist\n") : found = 0;
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
	if (close(env->fd) == -1)
		bug_err("Error while closing output file\n");
	return (1);
}
