/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:32:14 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 19:21:29 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		play_voice(const char *message)
{
	char	cmd[200];

	ft_memset(cmd, 0x00, 200);
	ft_strcat(cmd, "say -r 200 ");
	ft_strcat(cmd, message);
	if (system(cmd))
		perror("Invalid return");
}

void		play_sound(const char *file)
{
	char	cmd[200];

	ft_memset(cmd, 0x00, 200);
	ft_strcat(cmd, "afplay ");
	ft_strcat(cmd, file);
	if (system(cmd))
		perror("Invalid return");
}
