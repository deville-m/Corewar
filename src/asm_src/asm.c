/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/08 09:59:45 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void		init_env(t_env *env, char *input)
{
	env->tok_head = NULL;
	if (!(env->input_name = ft_strdup(input)))
		bug_err("Error malloc init_env");
}

int			main(int ac, char **av)
{
	t_env	env;

	if (!check_collisions((const char*)BASE, (const char*)LABEL_CHARS,
			(const char*)NAME_CMD_STRING,
			(const char *)COMMENT_CMD_STRING)
		|| ac != 2)
		return (1);
	else
	{
		init_env(&env, av[1]);
		stupid_asm(&env, av[1]);
	}
	return (0);
}
