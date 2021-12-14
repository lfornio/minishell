/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:04:18 by lfornio           #+#    #+#             */
/*   Updated: 2021/09/23 09:04:20 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src,
		size_t dstsize)
{
	size_t	j;
	size_t	res;
	size_t	len_src;
	size_t	len_dst;

	j = 0;
	len_dst = 0;
	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	while (dst[len_dst] && len_dst < dstsize)
		len_dst++;
	res = len_dst + len_src;
	while (src[j] && (len_dst + j + 1) < dstsize)
	{
		dst[len_dst + j] = src[j];
		j++;
	}
	if (len_dst < dstsize)
		dst[len_dst + j] = '\0';
	return (res);
}
