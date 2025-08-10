/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:22:45 by aosman            #+#    #+#             */
/*   Updated: 2025/06/13 15:31:45 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	size_t	len;

	last = NULL;
	c %= 128;
	len = ft_strlen(s);
	if (c == '\0' )
		return ((char *)(s + len));
	while (*s)
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	return ((char *)last);
}
