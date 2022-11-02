/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoded_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:22:51 by labenall          #+#    #+#             */
/*   Updated: 2022/10/25 11:59:36 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

char	res_mod1(int *n)
{
	int	r;

	r = *n / 16;
	if (r >= 10)
		r += 'a' - 10;
	else
		r += '0';
	*n %= 16;
	return (r);
}

char	res_mod2(int n)
{
	if (n >= 10)
		n += 'a' - 10;
	else
		n += '0';
	return (n);
}

char	*encodec_color(int r, int g, int b)
{
	char	*res;

	res = malloc(sizeof(char) * 9);
	res[0] = '0';
	res[1] = 'x';
	res[2] = res_mod1(&r);
	res[3] = res_mod2(r);
	res[4] = res_mod1(&g);
	res[5] = res_mod2(g);
	res[6] = res_mod1(&b);
	res[7] = res_mod2(b);
	res[8] = 0;
	return (res);
}
