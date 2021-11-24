/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:33 by tbousque          #+#    #+#             */
/*   Updated: 2021/11/24 20:35:02 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"
int	ft_printf(const char *str, ...)
{
	va_list aq;
	va_list ap;
	int int_arg;

	va_start(ap, str);	
	va_copy(aq, ap);
	while (*str)
	{
		if (*str == '%')
		{
			while (str == ' ')
				str++;
			if (str == 'd')
				return ;
		}
		write(1, str, 1);
	}
	int_arg = va_arg(aq, int);
	printf("%d", int_arg);
	va_end(aq);
	write(1, str, strlen(str));
}

int	main(int argc, char **argv)
{
	ft_printf("Bonjour", 42);
	return (0);
}
