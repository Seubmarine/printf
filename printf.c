/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:33 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/16 17:34:40 by tbousque         ###   ########.fr       */
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
	va_end(arg);
	return (size);
}

int	ft_snprintf(char *str, int size, const char *fmt, ...)
{
	va_list	arg;
	int i;
	(void) size;
	va_start(arg, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			if (fmt[i] == 'c')
				str[i] = va_arg(arg, int);
			else if (fmt[i] == '%')
				str[i] = '%';
		}
		str[i] = fmt[i];
		i++;
	}
	str[i] = '\0';
	va_end(arg);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list aq;
	va_list ap;
	int		size;
	char	*output;

	va_start(ap, str);	
	va_copy(aq, ap);
	size = get_size_of_entire_string(str, aq);
	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (-1);
	ft_snprintf(output, size + 1, str, ap);
	write(1, output, size);
	free(output);
	return (size);
}
