/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:30 by aosman            #+#    #+#             */
/*   Updated: 2025/08/10 13:08:06 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_get_params(char param, va_list args, int *count)
{
	if (param == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		*count += 1;
	}
	else if (param == 'd' || param == 'i')
		ft_put_nbr_fd(va_arg(args, int), 1, count);
	else if (param == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (param == 'u')
		ft_put_u_nbr_fd(va_arg(args, unsigned int), 1, count);
	else if (param == 'x')
		ft_puthex(va_arg(args, unsigned int), 0, count);
	else if (param == 'X')
		ft_puthex(va_arg(args, unsigned int), 1, count);
	else if (param == 'p')
		ft_putptr(va_arg(args, void *), count);
	else if (param == '%')
	{
		ft_putchar_fd('%', 1);
		(*count)++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			ft_get_params(str[i + 1], args, &count);
			i += 2;
		}
		else
		{
			count++;
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	va_end(args);
	return (count);
}
