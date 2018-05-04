/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:47:51 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/04 15:17:48 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "commons.h"
#include "op.h"

static t_bool	is_command(char *line)
{

}

/*
** Fills in the header structure (as defined in op.h)
** Parameter 1: file descriptor of the file beeing read
** Parameter 2: pointer to t_header structure
** NOTE: Integers are in the ENDIAN of the machine (little at 42).
**       prog_size is left empty due to the lack of information.
*/

void			parse_header(int fd, t_header *head)
{
	char *line;

	if (fd < 0 || !head)
		return (0);
	ft_bzero(head, sizeof(head));
	while (get_next_line(fd, &line) > 1 && is_empty(line))
		free(line);
}
