/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@42wolfsburg.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:34:21 by aosman            #+#    #+#             */
/*   Updated: 2025/06/09 20:25:46 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1 * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		res[i] = *s2;
		i++;
		s2++;
	}
	res [i] = '\0';
	return (res);
}
