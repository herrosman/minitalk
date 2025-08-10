/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:17:13 by aosman            #+#    #+#             */
/*   Updated: 2025/06/13 16:40:44 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*res;

	res = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		res[i] = (unsigned char)c;
		i++;
	}
	return (res);
}
