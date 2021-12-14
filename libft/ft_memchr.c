/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:02:22 by lfornio           #+#    #+#             */
/*   Updated: 2021/09/23 09:02:24 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s2;
	unsigned char		a;
	size_t				i;

	s2 = (const unsigned char *)s;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s2[i] == a)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
