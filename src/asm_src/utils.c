/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 14:35:52 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/04 15:01:19 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <libft.h>
#include <stdint.h>

/*
** @desc compute tab size
** @params args splitted arguments
** @return size of tabs
*/

uint8_t			arguments_size(const char **args)
{
	uint8_t		i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

/*
** @desc compute size of operators
** @params nil
** @return len of op array
*/

uint16_t		operator_tsize(void)
{
	return (sizeof(g_op_tab) / sizeof(g_op_tab[0]));
}
