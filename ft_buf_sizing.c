/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf_sizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:22:19 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/28 09:31:06 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline int	get_int_size_in_base(long n, int base)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
		size++;
	while (n)
	{
		n /= base;
		size++;
	}
	return (size);
}

static inline int	get_pointer_size(void *ptr)
{
	int					size;
	unsigned long long	n;

	if (ptr == NULL)
		return (sizeof(FT_NULL_PTR_STR) - 1);
	n = (unsigned long long) ptr;
	size = 2;
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}

static inline int	get_str_size(char *str)
{
	if (str == NULL)
		return (sizeof(FT_NULL_STR) - 1);
	return (ft_strlen(str));
}

//cast the next arg to given f and return size, -1 if error
int	size_of_arg(char f, va_list arg)
{
	if (f == 's')
		return (get_str_size(va_arg(arg, char *)));
	else if (f == 'c')
	{
		(void) va_arg(arg, int);
		return (1);
	}
	else if (f == '%')
		return (1);
	else if (f == 'x' || f == 'X')
		return (get_int_size_in_base(va_arg(arg, unsigned int), 16));
	else if (f == 'd' || f == 'i')
		return (get_int_size_in_base(va_arg(arg, int), 10));
	else if (f == 'u')
		return (get_int_size_in_base(va_arg(arg, unsigned int), 10));
	else if (f == 'p')
		return (get_pointer_size(va_arg(arg, void *)));
	return (-1);
}

//given a formated string and it's va_list, it return the size with the args
size_t	get_str_formated_size(const char *str, va_list arg)
{
	size_t	size;
	ssize_t	arg_size;

	size = 0;
	while (*str)
	{
		if (*str == '%')
		{
			arg_size = size_of_arg(*++str, arg);
			if (arg_size == -1)
				return (-1);
			size += arg_size;
		}
		else
			size++;
		str++;
	}
	va_end(arg);
	return (size);
}
