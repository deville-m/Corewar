/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:27:54 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 10:01:52 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	apply_speed(char input, t_scene *scene)
{
	if (input == 0x3c)
	{
		scene->speed += STEP_SPEED;
		if (scene->speed > MIN_SPEED)
			scene->speed = MIN_SPEED;
	}
	else if (input == 0x3e)
	{
		scene->speed -= STEP_SPEED;
		if (scene->speed < MAX_SPEED)
			scene->speed = MAX_SPEED;
	}
}

/*
** @desc keybind callback
** @return nil
*/

void		keybindinds_callback(char input,
					t_scene *scene)
{
	char	c;

	if (input == 0x71)
		exit(EXIT_SUCCESS);
	else if (scene->pause || input == 0x20)
	{
		scene->pause = 0;
		while (((c = getch()) != 0x20))
		{
			if (c == 0x71)
				exit(EXIT_SUCCESS);
			else if (c == 0x73)
			{
				scene->pause = 1;
				break ;
			}
		}
	}
	else
		apply_speed(input, scene);
}
