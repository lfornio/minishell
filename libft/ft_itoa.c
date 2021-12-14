/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:02:12 by lfornio           #+#    #+#             */
/*   Updated: 2021/09/23 09:02:14 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	perenos(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static unsigned int	delenie(unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

static int	znak(int nb)
{
	int	znak;

	if (nb < 0)
		znak = 1;
	else
		znak = 0;
	return (znak);
}

static char	*vivod(char *str, unsigned int nb, int i)
{
	while (nb >= 10)
	{
		str[i--] = nb % 10 + '0';
		nb = nb / 10;
	}
	str[i] = nb % 10 + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;
	unsigned int	dlina;

	nb = perenos(n);
	dlina = delenie(nb);
	str = (char *)malloc(sizeof(char) * (dlina + znak(n) + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		dlina = dlina + 1;
	}
	i = dlina - 1;
	str = vivod(str, nb, i);
	str[dlina] = '\0';
	return (str);
}
