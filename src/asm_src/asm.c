/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/08 09:54:43 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int	main(int ac, char **av)
{
	if (!check_collisions((const char*)BASE, (const char*)LABEL_CHARS,
				(const char*)NAME_CMD_STRING,
				(const char *)COMMENT_CMD_STRING)
		|| ac != 2)
		return (1);
	else
		stupid_asm(av[1]);
	return (0);
}
