/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:42:48 by aosman            #+#    #+#             */
/*   Updated: 2025/08/10 13:11:05 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex(unsigned long n, int upper, int *count)
{
	char	buf[17];
	char	*base;
	int		i;

	i = 16;
	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	buf[i--] = '\0';
	if (n == 0)
	{
		buf[i--] = '0';
		*count += 1;
	}
	while (n > 0)
	{
		buf[i--] = base[n % 16];
		n /= 16;
		*count += 1;
	}
	ft_putstr_fd(buf + i + 1, 1);
}
