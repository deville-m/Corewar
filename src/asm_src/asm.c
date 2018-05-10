/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/10 19:39:31 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "memory.h"
#include "ft_string.h"

void	tmp_make_fake_prog(t_env *env)
{
	// name
	create_token(env, COMMAND_NAME, 4, 2, ".name", 0, 0);
	create_token(env, COMMAND_COMMENT, 4, 2, "zork", 0, 0);
	// comment
	create_token(env, LABEL, 4, 2, ".comment", 0, 0);
	create_token(env, LABEL, 4, 2, "I'M ALIIIIVE", 0, 0);
	// label l2
	create_token(env, LABEL, 4, 2, "l2", 0, 0); //l2:
	// sti
	create_token(env, INSTRUCTION, 4, 2, "sti", 11, 1);
	// sti params
	create_token(env, REGISTER, 4, 2, "r1", 1, 1);
	create_token(env, DIRECT_LABEL, 4, 2, "live", 15, 1); //%:live
	create_token(env, DIRECT, 4, 2, "%1", 1, 1);
	// and
	create_token(env, INSTRUCTION, 4, 2, "and", 6, 1);
	// and params
	create_token(env, REGISTER, 4, 2, "r1", 1, 0);
	create_token(env, DIRECT, 4, 2, "%0", 0, 0);
	create_token(env, REGISTER, 4, 2, "r1", 1, 0);
	// label live
	create_token(env, LABEL, 4, 2, "live", 15, 0); //live:
	// live
	create_token(env, INSTRUCTION, 4, 2, "live", 1, 0);
	// live param
	create_token(env, DIRECT, 4, 2, "%1", 1, 0);
	// zjmp
	create_token(env, INSTRUCTION, 4, 2, "zjmp", 9, 0);
	// zjmp param
	create_token(env, DIRECT_LABEL, 4, 2, "live", 15, 1);//%:live

	ft_lstreverse(&(env->tok_head));
}

static void	init_header(t_env *env)
{
	env->header->magic = (int)COREWAR_EXEC_MAGIC;
	swap_endian((void *)&env->header->magic, sizeof(env->header->magic));
	ft_bzero(env->header->prog_name, PROG_NAME_LENGTH + 1);
	env->header->prog_size = 0;
	ft_bzero(env->header->comment, COMMENT_LENGTH + 1);
}


static void	init_env(t_env *env, char *input)
{
	env->tok_head = NULL;
	if (!(env->input_name = ft_strdup(input)))
		bug_err("Error malloc init_env\n");
	env->header = (t_header *)malloc(sizeof(t_header));
	if (!env->header)
		bug_err("Error while creating header\n");
	env->lab_h = NULL;
	env->to_do = NULL;
	env->fd = -1;
}

int		main(int ac, char **av)
{
	t_env	env;

	if (check_collisions(0) == FALSE || ac != 2)
		return (1);
	else
	{
		init_env(&env, av[1]);
		init_header(&env);

		tmp_make_fake_prog(&env); //fake

		craft_file(&env);
	}
	return (0);
}
