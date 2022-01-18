/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:33 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/18 21:03:32 by tbousque         ###   ########.fr       */
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

int	parse_size(char f, va_list *arg)
{
	if (f == 's')
		return (ft_strlen(va_arg(*arg, char *)));
	else if (f == 'c' || f == '%')
		return (1);
	else if (f == 'x' || f == 'X')
		return (get_int_size_in_base(va_arg(*arg, int), 16));
	else if (f == 'd' || f == 'i')
		return (get_int_size_in_base(va_arg(*arg, int), 10));
	else if (f == 'u')
		return (get_int_size_in_base((unsigned int) va_arg(*arg, unsigned int), 10));
	else if (f == 'p')
		return (get_pointer_size(va_arg(*arg, void *)));
	return (-1);
}

int	get_size_of_entire_string(const char *str, va_list arg)
{
	int	size;
	int	arg_size;

	size = 0;
	while(*str)
	{
		if (*str == '%')
		{
			arg_size = parse_size(*++str, &arg)
			if (arg_size = -1)
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

//buffer size is the number of byte still assignable in str
int	parse_buf(char fmt, char *str, size_t buffer_size, va_list arg)
{
	char	*base16;

	if (fmt == 'p' || fmt == 'x' || fmt == 'X')
	{
		base16 = "0123456789abcdef"
		if (fmt == 'p')
			ft_strlcat(str, "0x");
		if (fmt == 'X')
			base16 = "0123456789ABCDEF"
		return (ft_snullbase(str + (2 * fmt == 'p'), size, (unsigned long long)va_arg(arg, void *), base16));
	}
	else if (fmt == 's')
		return (ft_strlcat(str, va_arg(arg, char *)));
	else if (fmt == 'i' || fmt == 'd')
		return (ft_snullbase(str, size, va_arg(arg, int), "0123456789"));
	else if (fmt == 'u')
		return (ft_snullbase(str, size, va_arg(arg, unsigned int), "0123456789"));
	else if (fmt == 'c')
		str[0] = va_arg(arg, int);
	else if (fmt == '%')
		str[0] = '%';
	return (1);
}

int	ft_snprintf(char *str, int size, const char *fmt, ...)
{
	va_list	arg;
	int i;
	(void) size;
	va_start(arg, fmt);
	while (fmt[i])
	{
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
