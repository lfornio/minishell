/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:03:09 by lfornio           #+#    #+#             */
/*   Updated: 2021/09/23 09:12:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	net_c(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	stroki(const char *s, char c)
{
	int	i;
	int	len;
	int	end;
	int	minus;

	i = 0;
	len = 0;
	minus = 0;
	if ((ft_strlen(s) == 0) || (*s == 0 && c == 0))
		return (0);
	if (net_c(s, c) == 0)
		return (1);
	while (s[i] && s[i] == c)
		i++;
	while (s[i++])
	{
		if (s[i - 1] == c && s[i] != c)
			len++;
	}
	end = ft_strlen(s) - 1;
	while (s[end--] == c)
		minus = 1;
	return (len - minus + 1);
}

void	m_malloc(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*slovo(char const *s, char c, int i, char **arr)
{
	char	*slovo;
	int		len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	slovo = (char *)malloc(sizeof(char) * (len + 1));
	if (slovo == NULL)
	{
		m_malloc(arr);
		return (NULL);
	}
	slovo[len] = '\0';
	while (len-- && s[i - 1] != c)
	{
		slovo[len] = s[i - 1];
		i--;
	}
	return (slovo);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (stroki(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (k < stroki(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		tab[k] = slovo(s, c, i, tab);
		while (s[i] && s[i] != c)
			i++;
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
