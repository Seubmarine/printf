/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 08:18:08 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/28 09:11:52 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline int	pointer_in_buf(char *buf, size_t size, va_list arg)
{
	void	*ptr;

	ptr = va_arg(arg, void *);
	if (ptr == NULL)
		return (ft_strlcat(buf, FT_NULL_PTR_STR, size));
	ft_strlcat(buf, "0x", size);
	return (2 + ft_snullbase(buf + 2, size, (ptrdiff_t)ptr, BASE16_MIN));
}

static inline int	int_in_buf(char *buf, size_t size, va_list arg)
{
	long	i;

	i = va_arg(arg, int);
	if (i < 0)
	{
		ft_strlcat(buf, "-", size);
		return (1 + ft_snullbase(buf + 1, size, -i, "0123456789"));
	}
	return (ft_snullbase(buf, size, i, "0123456789"));
}

static inline int	hexa_in_buf(char *buf, size_t size, char fmt, va_list arg)
{
	char	*base16;

	base16 = BASE16_MIN;
	if (fmt == 'X')
		base16 = BASE16_MAJ;
	return (ft_snullbase(buf, size, va_arg(arg, unsigned int), base16));
}

static inline int	str_in_buf(char *buf, size_t size, va_list arg)
{
	char	*str;

	str = va_arg(arg, char *);
	if (str == NULL)
		return (ft_strlcat(buf, FT_NULL_STR, size));
	return (ft_strlcat(buf, str, size));
}

//size is the number of byte still assignable in buf
int	arg_in_buf(char *buf, size_t size, char fmt, va_list arg)
{
	if (fmt == 'p')
		return (pointer_in_buf(buf, size, arg));
	if (fmt == 'x' || fmt == 'X')
		return (hexa_in_buf(buf, size, fmt, arg));
	else if (fmt == 's')
		return (str_in_buf(buf, size, arg));
	else if (fmt == 'i' || fmt == 'd')
		return (int_in_buf(buf, size, arg));
	else if (fmt == 'u')
		return (ft_snullbase(buf, size, va_arg(arg, unsigned), "0123456789"));
	else if (fmt == 'c')
		buf[0] = va_arg(arg, int);
	else if (fmt == '%')
		buf[0] = '%';
	return (1);
}
