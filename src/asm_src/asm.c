/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/13 15:56:53 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "asm.h"
#include "op.h"
#include "memory.h"
#include "ft_string.h"
#include "libft.h"
#include "dlst.h"

void	print_tokens(t_dlist *elem)
{
	t_asm_token *token;

	token = (t_asm_token *)elem->content;
	if (token->type == ENDLINE)
		ft_printf("type: ENDLINE\n");
	else if (token->type == END)
		ft_printf("type: END\n");
	else
		ft_printf("type: %d -- raw: %s -- data: %d -- option: %d\n",
				token->type, token->raw, token->data, token->option);
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

int			main(int argc, char **argv)
{
	t_env	env;
	int		fd;

	if (!check_collisions((const char*)BASE, (const char*)LABEL_CHARS,
			(const char*)NAME_CMD_STRING,
			(const char *)COMMENT_CMD_STRING)
		|| argc != 2)
		bug_err("Wrong arguments format\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		bug_err("Error while opening file\n");
	init_env(&env, argv[1]);
	init_header(&env);
	if (!(env.tok_head = (t_list *)tokenize(fd)))
		bug_err("");
	env.tok_head = (t_list *)syntax_check((t_dlist *)env.tok_head);
	craft_file(&env);
	ft_printf("Writing output program to %s\n", env.input_name);
//	ft_dlstiter((t_dlist *)env.tok_head, print_tokens);
//	ft_dlstdel(&((t_dlist *)env.tok_head), del_token);
	close(fd);
	return (0);
}
