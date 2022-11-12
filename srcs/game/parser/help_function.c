/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:43:37 by labenall          #+#    #+#             */
/*   Updated: 2022/10/23 11:39:09 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

//hana ekanpranti ach man erreur lga o exit moraha
void	exit_erreur(char *s)
{
	printf("Error\n%s\n", s);
	exit(1);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((s1[i] - s2[i]));
}

int	is_sapce(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

//ghan7ayad + man atoi
int	ft_atoi(char *s)
{
	size_t	i;
	int		res;

	if (ft_strlen(s) == 0)
		exit_erreur("nbr not good");
	i = 0;
	res = 0;
	while (s[i])
	{
		res = res * 10 + s[i] - '0';
		i++;
		if (res > 255)
			exit_erreur("nbr > 255");
	}
	return (res);
}
