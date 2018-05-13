/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:27:54 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 13:35:38 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc keybind callback
** @return nil
*/

void	keybindinds_callback(int c)
{
	if (c == 0x1b || c == 0x71)
		return ((void)EXIT_SUCCESS);
}
