/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:18:52 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/09 15:04:36 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "op.h"
#include "get_next_line.h"
#include "asm.h"
#include "dlst.h"

void	print_tokens(t_dlist *elem)
{
	t_asm_token *token;

	token = (t_asm_token *)elem->content;
	if (token->type == ENDLINE)
		ft_printf("type: ENDLINE\n");
	else
		ft_printf("type: %d, %s\n", token->type, token->data);
}

int		main(int argc, char *const argv[])
{
	int		fd;
	t_dlist	*tokens;

	if (argc != 2)
		exit(42);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		exit(42);
	if (!(tokens = tokenize(fd)))
		exit(42);
	ft_dlstreverse(&tokens);
	ft_dlstiter(tokens, print_tokens);
	close(fd);
}
