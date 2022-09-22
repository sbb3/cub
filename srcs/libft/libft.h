/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:14:04 by adouib            #+#    #+#             */
/*   Updated: 2022/01/03 12:14:06 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

char	**ft_split(char *s, char c);
int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr(char *s, char c);
char	*ft_strrchr(char *s, int c);
int		ft_strrstr(const char *haystack, const char *needle, int n);

#endif
