/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:37:56 by aosman            #+#    #+#             */
/*   Updated: 2025/06/13 13:48:32 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(little);
	if (needle_len == 0)
		return ((char *)big);
	if (len < needle_len)
		return (NULL);
	while (*big && len >= needle_len)
	{
		if (len >= needle_len)
		{
			i = 0;
			while (i < needle_len && big[i] == little[i])
				i++;
			if (i == needle_len)
				return ((char *)big);
			big++;
			len--;
		}
	}
	return (NULL);
}
