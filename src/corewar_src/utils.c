/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/09 17:22:47 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>

/*
** @desc print usage and exit;
** @return Nil (exit)
*/

void	usage(void)
{
	ft_printf("Usage: ./corewar [-d nbr_cycles] ");
	ft_printf("[[-n number] champion1.cor] ...\n");
	exit(EXIT_FAILURE);
}
