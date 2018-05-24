/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:27:54 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 09:46:41 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc keybind callback
** @return nil
*/

void	keybindinds_callback(int c)
{
	if (c == KEY_ENTER)
		return ((void)EXIT_SUCCESS);
}
