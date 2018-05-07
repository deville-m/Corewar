/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:15:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 15:56:22 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int	main(int ac, char **av)
{
	t_bool s;
	printf("0x%.2x status: %s\n", is_params_ok(1, "r2,%u", &s), (s == TRUE) ? "SUCCESS" : "FAILURE");
	printf("0x%.2x status: %s\n", is_params_ok(1, "r2,23,%34", &s), (s == TRUE) ? "SUCCESS" : "FAILURE");
	printf("0x%.2x status: %s\n", is_params_ok(1, "23,45,%34", &s), (s == TRUE) ? "SUCCESS" : "FAILURE");
	printf("0x%.2x status: %s\n", is_params_ok(1, "r1,r3,34", &s), (s == TRUE) ? "SUCCESS" : "FAILURE");
	printf("0x%.2x status: %s\n", is_params_ok(1, "r1,r3|34", &s), (s == TRUE) ? "SUCCESS" : "FAILURE");
	if (ac != 2)
		return (1);
	else
		stupid_asm(av[1]);
	return (0);
}
