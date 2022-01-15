/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:49:40 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/15 01:57:56 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include "libft.h"

# if __linux__
#  define NULL_PTR_STR "(nil)"
# else
#  define NULL_PTR_STR "0x0"
# endif

int	ft_printf(const char *, ...);
#endif
