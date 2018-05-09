/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 20:08:40 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "windows.h"

static void swap_endian(void *data, size_t size)
{
	char	tmpdata;
	char	*tmp;
	size_t	i;

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

void	tmp_make_fake_header(t_env *env)
{
	int	magic;

	magic = (int)COREWAR_EXEC_MAGIC;
	env->header->magic = magic;
	swap_endian((void *)&env->header->magic, sizeof(magic));
	ft_bzero(env->header->prog_name, PROG_NAME_LENGTH + 1);
	ft_memcpy(env->header->prog_name, "zork", 4); // sooo fake
	env->header->prog_size = 0x17; // sooo fake; corresponds to zork
	swap_endian((void *)&env->header->prog_size, sizeof(unsigned int));
	ft_bzero(env->header->comment, COMMENT_LENGTH + 1);
	ft_memcpy(env->header->comment, "just a basic living prog", 24); // sooo fake
}

void	tmp_make_fake_prog(t_env *env)
{
	// label l2
	create_token(env, LABEL, 4, 2, "l2:", 0);
	// sti
	create_token(env, INSTRUCTION, 4, 2, "sti", 11);
	// sti params
	create_token(env, REGISTER, 4, 2, "r1", 1);
	create_token(env, DIRECT_LABEL, 4, 2, "%:live", 15);
	create_token(env, DIRECT, 4, 2, "%1", 1);
	// and
	create_token(env, INSTRUCTION, 4, 2, "and", 6);
	// and params
	create_token(env, REGISTER, 4, 2, "r1", 1);
	create_token(env, DIRECT, 4, 2, "%0", 0);
	create_token(env, REGISTER, 4, 2, "r1", 1);
	// label live
	create_token(env, LABEL, 4, 2, "live:", 15);
	// live
	create_token(env, INSTRUCTION, 4, 2, "live", 1);
	// live param
	create_token(env, DIRECT, 4, 2, "%1", 1);
	// zjmp
	create_token(env, INSTRUCTION, 4, 2, "zjmp", 9);
	// zjmp param
	create_token(env, DIRECT_LABEL, 4, 2, "%:live", 15);
}

void	init_env(t_env *env, char *input)
{
	env->tok_head = NULL;
	if (!(env->input_name = ft_strdup(input)))
		bug_err("Error malloc init_env\n");
	env->header = (t_header *)malloc(sizeof(t_header));
	if (!env->header)
		bug_err("Error while creating header\n");

}

int		main(int ac, char **av)
{
	t_env	env;

	if (check_collisions(0) == FALSE || ac != 2)
		return (1);
	else
	{
		init_env(&env, av[1]);

		tmp_make_fake_header(&env); // sooo fake
		tmp_make_fake_prog(&env);

		craft_file(&env);
	}
	return (0);
}
