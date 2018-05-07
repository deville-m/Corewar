/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:47:51 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/07 14:02:34 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "commons.h"
#include "op.h"

/*
** Fills in the header structure (as defined in op.h)
** Parameter 1: list of tokens
** Parameter 2: pointer to t_header structure
** NOTE: Integers are in the ENDIAN of the machine (little at 42).
**       prog_size is left empty due to the lack of information.
*/

void			parse_header(t_dlist *tokens, t_header *head)
{
}
