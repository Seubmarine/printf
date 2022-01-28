/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:33 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/28 09:31:18 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vsnprintf(char *buf, size_t size, const char *fmt, va_list ap)
{
	va_list	arg_buf;
	size_t	buf_i;
	size_t	fmt_i;

	va_copy(arg_buf, ap);
	buf_i = 0;
	fmt_i = 0;
	while (buf_i < size && fmt[fmt_i])
	{
		if (fmt[fmt_i] == '%')
		{
			fmt_i++;
			buf_i += arg_in_buf(buf + buf_i, size - buf_i, fmt[fmt_i], arg_buf);
			fmt_i++;
		}
		else
		{
			buf[buf_i] = fmt[fmt_i];
			buf_i++;
			fmt_i++;
		}
	}
	return (buf_i);
}

int	ft_snprintf(char *buf, size_t size, const char *format, ...)
{
	int		how_much_writed;
	va_list	ap;

	va_start(ap, format);
	how_much_writed = ft_vsnprintf(buf, size, format, ap);
	va_end(ap);
	return (how_much_writed);
}

int	ft_printf(const char *format, ...)
{
	char	*buf;
	size_t	buf_size;
	size_t	size_used;
	va_list	ap;
	va_list	arg_size;

	buf = NULL;
	va_start(ap, format);
	va_copy(arg_size, ap);
	buf_size = get_str_formated_size(format, arg_size) + 1;
	buf = malloc(sizeof(char) * buf_size);
	if (!buf)
		return (-1);
	ft_memset(buf, 0, buf_size);
	size_used = ft_vsnprintf(buf, buf_size, format, ap);
	write(1, buf, size_used);
	free(buf);
	return (buf_size - 1);
}
