/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalHelpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:44:06 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 02:02:37 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		exit_if_null(ptr, "Allocation failed");
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	correct_angle(float *angle)
{
	if (*angle < 0)
		*angle = 360 + *angle;
	if (*angle > 360)
		*angle = *angle - 360;
}

float	fix_angle(float angle)
{
	if (angle < 0)
		return (360 + angle);
	else if (angle > 360)
		return (angle - 360);
	return (angle);
}

float	deg_2_rad(float angleInDegree)
{
	return ((angleInDegree * M_PI) / 180);
}
