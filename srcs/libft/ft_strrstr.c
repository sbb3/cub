/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:14:01 by adouib            #+#    #+#             */
/*   Updated: 2022/01/03 12:14:02 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrstr(const char *haystack, const char *needle, int n)
{
	int	sizeh;
	int	sizen;

	sizeh = ft_strlen(haystack) - 1;
	sizen = ft_strlen(needle) - 1;
	while (haystack[sizeh--] == needle[sizen--] && n)
		n--;
	if (n == 0)
		return (1);
	return (0);
}
