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
/*
void	tmp_make_fake_prog(t_env *env)
{
	create_token(*env, LABEL, 4, 2, "name:");
}
*/
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

		craft_file(&env);
	}
	return (0);
}
