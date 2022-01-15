/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:33 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/15 01:42:07 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

int get_int_size_in_base(int n, int base)
{
	int	size;

	size = 0 + (1 * n < 0);
	while (n)
	{
		n /= base;
		size++;
	}
	
	return (size);
}

int get_pointer_size(void *ptr)
{
	int					size;
	unsigned long long	n;

	if (ptr == NULL)
		return (sizeof(NULL_PTR_STR) - 1);
	n = (unsigned long long) ptr;
	size = 2;
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}

int	get_size_of_entire_string(const char *str, va_list arg)
{
	int	size;

	size = 0;
	while(*str)
	{
		if (*str == '%')
		{	
			str++;
			if (*str == 's')
				size += ft_strlen(va_arg(arg, char *));
			else if (*str == 'c' || *str == '%')
				size++;
			else if (*str == 'x' || *str == 'X')
				size += get_int_size_in_base(va_arg(arg, int), 16);
			else if (*str == 'd' || *str == 'i')
				size += get_int_size_in_base(va_arg(arg, int), 10);
			else if (*str == 'u')
				size += get_int_size_in_base((unsigned int) va_arg(arg, unsigned int), 10);
			else if (*str == 'p')
				size += get_pointer_size(va_arg(arg, void *));
		}
		else
			size++;
		str++;
	}
	return (size);
}

int	ft_printf(const char *str, ...)
{
	va_list aq;
	va_list ap;
	int		size;

	va_start(ap, str);	
	va_copy(aq, ap);
	size = get_size_of_entire_string(str, aq);
	va_end(aq);
	return (size);
}
