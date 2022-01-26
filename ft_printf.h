/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:49:40 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/26 14:35:39 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# define FT_NULL_STR "(null)"

# if defined (__APPLE__)
#  define FT_NULL_PTR_STR "0x0"
# elif __linux__
#  define FT_NULL_PTR_STR "(nil)"
# endif

int	ft_printf(const char *, ...);
int	ft_snprintf(char *buf, size_t size, const char *format, ...);
int	ft_vsnprintf(char *buf, size_t size, const char *format, va_list ap);
#endif
