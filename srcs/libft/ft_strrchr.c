/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:13:58 by adouib            #+#    #+#             */
/*   Updated: 2022/01/03 12:13:59 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	size;

	size = ft_strlen(s) + 1;
	while (size-- > 0)
	{
		if (s[size] == c)
			return ((char *)s + size);
	}
	return (0);
}
