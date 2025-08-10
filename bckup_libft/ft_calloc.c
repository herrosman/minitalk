/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:09:05 by aosman            #+#    #+#             */
/*   Updated: 2025/06/13 16:07:33 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			length;
	unsigned char	*ptr;
	size_t			i;

	length = nmemb * size;
	if (nmemb != 0 && size != 0 && length / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(length);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < length)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
