/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:02:52 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/10 18:53:19 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

t_lab			*new_t_lab(char *name, int offset, int instr_offset)
{
	t_lab	*new;

	new = (t_lab *)malloc(sizeof(t_lab));
	if (!new)
		bug_err("Error with t_lab malloc.\n");
	new->name = name;
	new->offset = offset;
	new->instr_offset = instr_offset;
	return (new);
}

unsigned char	craft_coding_byte(t_list *head)
{
	t_asm_token		*tmp;
	unsigned char	result;
	int				i;

	i = 2;
	result = 0;
	if (!head)
		return (0);
	tmp = (t_asm_token *)head->content;
	while (head && tmp && LABEL < tmp->type && tmp->type < SEPARATOR)
	{
		if (tmp->type == REGISTER)
			result |= 1;
		else if (tmp->type == DIRECT || tmp->type == DIRECT_LABEL)
			result |= 2;
		else
			result |= 3;
		result <<= 2;
		i -= 1;
		head = head->next;
		tmp = (t_asm_token *)head->content;
	}
	while (i-- >= 0)
		result <<= 2;
	return (result);
}

int				craft_instru(t_env *env, t_list *current, int offset, int *in_off)
{
	t_asm_token		*tok;
	unsigned char	c;

	*in_off = offset;
	if (!current)
		bug_err("Error while trying to craft instruction\n");
	if (!(tok = (t_asm_token *)current->content))
		bug_err("Error while trying to craft instruction\n");
	offset += write(env->fd, &(tok->data), 1);
	if (tok->option)
	{
		if (!(c = craft_coding_byte(current->next)))
			bug_err("Error while crafting coding byte\n");
		offset += write(env->fd, &c, 1);
	}
	return (offset);
}

t_lab			*is_labelled(t_env *env, t_asm_token *tok)
{
	t_list	*tmp;
	t_lab	*elem;

	tmp = env->lab_h;
	while (tmp)
	{
		elem = (t_lab *)tmp->content;
		if (ft_strcmp(elem->name, tok->raw) == 0)
			return (elem);
		tmp = tmp->next;
	}
	return (NULL);
}

int				craft_labels(t_env *env, t_asm_token *tok, int offset, int instr_offset)
{
	t_lab	*tmp;
	short	result;

	if ((tmp = is_labelled(env, tok)))
	{
		result = (short)(tmp->offset - instr_offset);
		swap_endian(&(result), 2);
		offset += write(env->fd, &result, 2);
	}
	else
	{
		tmp = new_t_lab(tok->raw, offset, instr_offset);
		ft_lstinsert(&(env->to_do), tmp, sizeof(t_lab));
		offset += write(env->fd, "aa", 2);
	}
	return (offset);
}

int				craft_values(t_env *env, t_asm_token *tok, int offset)
{
	short	tmp;

	tmp = 0;
	if (tok->option || tok->type == INDIRECT)
	{
		tmp = (short)tok->data;
		swap_endian(&tmp, 2);
		offset += write(env->fd, &tmp, 2);
	}
	else
	{
		swap_endian(&(tok->data), 4);
		offset += write(env->fd, &(tok->data), 4);
	}
	return (offset);
}

void			fill_label_gaps(t_env *env, int	offset, t_list *haystack)
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
void			add_lab_elem(t_env *env, t_asm_token *tok, int offset)
{
	t_lab	*new;

	new = new_t_lab(tok->raw, offset, -1);
	ft_lstinsert(&(env->lab_h), (void *)new, sizeof(t_lab));
}

int		craft_file(t_env *env)
{
	int	last_offset;

	env->fd = create_output_file(env);
	write(env->fd, env->header, sizeof(t_header));
	last_offset = craft_prog(env, env->tok_head);
	fill_label_gaps(env, last_offset, NULL);
	if (lseek(env->fd, 0, SEEK_SET) == -1)
		bug_err("Error while last lseek for writing header\n");
	swap_endian(&(env->header->prog_size), 4);
	write(env->fd, env->header, sizeof(t_header));
	return (1);
}
