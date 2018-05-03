/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:33:54 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/03 17:41:07 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

typedef enum	e_bool
{
	FALSE = 0,
	TRUE = 1
}				t_bool;

typedef struct		s_proc
{
	int				player_id;
	char			PC[REG_SIZE];
	t_bool			carry;
	char			reg[REG_NUMBER][REG_SIZE];
}					t_proc;
