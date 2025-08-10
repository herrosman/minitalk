/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:49:20 by aosman            #+#    #+#             */
/*   Updated: 2025/06/12 19:25:20 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	len;
	size_t	s;
	size_t	e;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	while (s1[s] && is_in_set(s1[s], set))
		s++;
	e = ft_strlen(s1);
	while (e > s && is_in_set(s1[e - 1], set))
		e--;
	len = e - s;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	len = ft_strlcpy(res, s1 + s, len + 1);
	return (res);
}
