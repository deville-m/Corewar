/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/04 14:54:45 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <libft.h>

# define P_OUTRANGE(x, y) (x < 1 || x > y)

void			stupid_asm(char *in_name);

/*
** @predicate.c
*/

char			is_instruct(const char *line);
t_bool			is_empty(const char *line);
char			is_params_ok(const char opcode,
							const char *params,
							t_bool *status);

/*
** @utils.c
*/

uint8_t			arguments_size(const char **args);
uint16_t		operator_tsize(void);

#endif
