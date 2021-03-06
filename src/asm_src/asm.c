/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/06/07 14:18:03 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "asm.h"
#include "op.h"
#include "memory.h"
#include "ft_string.h"
#include "libft.h"
#include "dlst.h"

static void	free_t_lab(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
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
	ft_bzero(env->header, sizeof(t_header));
	env->header->magic = (int)COREWAR_EXEC_MAGIC;
	swap_endian((void *)&env->header->magic, sizeof(env->header->magic));
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		fd;

	if (!check_collisions((const char *)BASE, (const char *)LABEL_CHARS)
		|| argc != 2)
		bug_err("Wrong arguments format\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		bug_err("Error while opening file\n");
	init_env(&env, argv[1]);
	if (!(env.tok_head = (t_list *)tokenize(fd)))
		bug_err("Empty file");
	env.tok_head = (t_list *)syntax_check((t_dlist *)env.tok_head);
	craft_file(&env);
	ft_printf("Writing output program to %s\n", env.input_name);
	ft_dlstdel((t_dlist **)&env.tok_head, del_token);
	ft_dlstdel((t_dlist **)&env.lab_h, free_t_lab);
	ft_dlstdel((t_dlist **)&env.to_do, free_t_lab);
	free(env.header);
	free(env.input_name);
	close(fd);
	return (0);
}
