/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:04:50 by lfornio           #+#    #+#             */
/*   Updated: 2021/09/23 09:04:52 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ravno(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	a;
	size_t	z;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	z = ft_strlen(s1);
	while (s1[i] != '\0' && ravno(s1[i], set) == 1)
		i++;
	a = i;
	while (z > a && ravno(s1[z - 1], set))
		z--;
	str = (char *)malloc(sizeof(char) * (z - a + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (a < z)
		str[i++] = s1[a++];
	str[i] = '\0';
	return (str);
}
