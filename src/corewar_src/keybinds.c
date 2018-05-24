/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:27:54 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 17:01:05 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc keybind callback
** @return nil
*/

void	keybindinds_callback(char input,
					t_scene *scene)
{
	char	c;

	if (input == 0x71)
		exit(EXIT_SUCCESS);
	else if (input == 0x20)
	{
		while (((c = getch()) != 0x20))
			if (c == 0x71)
				exit(EXIT_SUCCESS);
	}
	else if (input == 0x3c)
	{
		scene->speed -= 1000;
		if (scene->speed < 1)
			scene->speed = 1;
	}
	else if (input == 0x3e)
	{
		scene->speed += 1000;
		if (scene->speed > 10000)
			scene->speed = 10000;
	}
}
