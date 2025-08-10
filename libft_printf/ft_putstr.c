/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:39:32 by aosman            #+#    #+#             */
/*   Updated: 2025/08/10 13:10:33 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str, int *count)
{
	if (str == NULL)
	{
		write (1, "(null)", 6);
		*count += 6;
	}
	else
	{
		ft_putstr_fd(str, 1);
		*count += ft_strlen(str);
	}
}
