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
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int	ft_printf(const char *str, ...)
{
	va_list aq;
	va_list ap;
	void *current_arg;

	va_start(ap, str);	
	va_copy(aq, ap);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			while (*str == ' ')
				str++;
			if (*str == 'd')
				ft_putnbr_fd(va_arg(aq, int), 1);
			else if (*str == 'c')
				ft_putchar_fd(va_arg(aq, int), 1);
			else if (*str == 's')
				ft_putstr_fd(va_arg(aq, char *), 1);
			else if (*str == '%')
				ft_putchar_fd('%', 1);
			else if (*str == 'p' || *str == 'x')
			{
				char *hex = ft_ullbase(va_arg(aq, unsigned long long), "0123456789abcedf", 16, 0);
				if (*str == 'p')
					write(1, "0x", 2);
				ft_putstr_fd(hex, 1);
				free(hex);
			}
			str++;
		}
		if (!*str)
			break;
		write(1, str, 1);
		str++;
	}
	va_end(aq);
	return (0);
}

int	main(int argc, char **argv)
{
	int n = 42;
	const char *str = "Bonjour je m'appel %s j'ai %d ans\npointer of %d is %p\n";
	printf(str, "Théo", 19, n, &n);
	ft_printf(str, "Théo", 19, n, &n);
	printf("linux return : %p\n", NULL);
	ft_printf("I return : %p\n", NULL);
	return (0);
}
