/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GeneralHelpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:44:06 by adouib            #+#    #+#             */
/*   Updated: 2022/10/25 17:08:04 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

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

/*
		// 360%360=0; 0%360=0; 362%360=2 42%360=42; -1%360=359
		// return (angle % 360); // a<0 360-a < 360-360=0 <a-360
*/
void	correct_angle(float *angle)
{
	if (*angle < 0)
		*angle = 360 + *angle;
	if (*angle > 360)
		*angle = *angle - 360;
}
