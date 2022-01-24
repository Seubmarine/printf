/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:33 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/24 12:57:08 by tbousque         ###   ########.fr       */
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

int	parse_size(char f, va_list arg)
{
	if (f == 's')
		return (ft_strlen(va_arg(arg, char *)));
	else if (f == 'c' || f == '%')
		return (1);
	else if (f == 'x' || f == 'X')
		return (get_int_size_in_base(va_arg(arg, int), 16));
	else if (f == 'd' || f == 'i')
		return (get_int_size_in_base(va_arg(arg, int), 10));
	else if (f == 'u')
		return (get_int_size_in_base((unsigned int) va_arg(arg, unsigned int), 10));
	else if (f == 'p')
		return (get_pointer_size(va_arg(arg, void *)));
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
			arg_size = parse_size(*++str, arg);
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

//buffer size is the number of byte still assignable in str
int	arg_in_buf(char *buf, char fmt, size_t size, va_list arg)
{
	char	*base16;

	if (fmt == 'p' || fmt == 'x' || fmt == 'X')
	{
		base16 = "0123456789abcdef";
		if (fmt == 'p')
			ft_strlcat(buf, "0x", 2);
		if (fmt == 'X')
			base16 = "0123456789ABCDEF";
		return (ft_snullbase(buf + (2 * (fmt == 'p')), size, (unsigned long long)va_arg(arg, void *), base16));
	}
	else if (fmt == 's')
	{
		char *arg_str = va_arg(arg, char *);
		return (ft_strlcat(buf, arg_str, size));
	}
	else if (fmt == 'i' || fmt == 'd')
		return (ft_snullbase(buf, size, va_arg(arg, int), "0123456789"));
	else if (fmt == 'u')
		return (ft_snullbase(buf, size, va_arg(arg, unsigned int), "0123456789"));
	else if (fmt == 'c')
		buf[0] = va_arg(arg, int);
	else if (fmt == '%')
		buf[0] = '%';
	return (1);
}

int	ft_vsnprintf(char *buf, size_t size, const char *format, va_list ap)
{
	va_list arg_for_buf;
	size_t	buf_index;
	size_t	format_index;
	
	va_copy(arg_for_buf, ap);
	buf_index = 0;
	format_index = 0;
	while (buf_index < size)
	{
		if (format[format_index] == '%')
		{
			format_index++;
			buf_index += arg_in_buf(buf + buf_index, format[format_index], size - buf_index, arg_for_buf);
			format_index++;
			
		}
		else
		{
			buf[buf_index] = format[format_index];
			buf_index++;
			format_index++;
		}
	}
	return (buf_index);
}

int	ft_snprintf(char *buf, size_t size, const char *format, ...)
{
	int	how_much_writed;
	va_list	ap;

	va_start(ap, format);
	how_much_writed = ft_vsnprintf(buf, size, format, ap);
	va_end(ap);
	return (how_much_writed);
}
