/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <mdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 14:12:21 by mdeville          #+#    #+#             */
/*   Updated: 2018/01/17 15:44:43 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iscntrl(int c)
{
	return ((c >= 000 && c <= 037) || c == 0177);
}
