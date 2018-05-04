/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:04:07 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/04 18:01:45 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define EOL 'q'
#include "get_next_line.h"
/*
** Coreware virtual machine
** main entry point
** @return succuss code
*/

int		main()
{
	char *line;

	while (get_next_line(0, &line))
	{
		printf("%s\n", line);
		free(line);
	}
    return (0);
}
