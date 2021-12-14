/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:04:46 by lfornio           #+#    #+#             */
/*   Updated: 2021/09/23 09:04:48 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	a;

	i = 0;
	while (s[i] != '\0')
		i++;
	a = i;
	while (a > 0)
	{
		if (s[a] != (char)c)
			a--;
		if (s[a] == (char)c)
			return ((char *)s + a);
	}
	if (s[0] == '\0' && s[0] == (char)c)
		return ((char *)s + a);
	return (NULL);
}
