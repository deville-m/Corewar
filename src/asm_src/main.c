/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:18:52 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/07 16:04:35 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "op.h"
#include "get_next_line.h"
#include "asm.h"
#include "dlst.h"

int	main(int argc, char *const argv[])
{
	int		fd;
	t_dlist	*tokens;

	if (argc != 2)
		exit(42);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		exit(42);
	if (!(tokens = tokenize(fd)))
		exit(42);
//	ft_dlstiter(tokens, print_token);
	close(fd);
}
