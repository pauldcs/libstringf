/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iob_format_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:08:10 by pducos            #+#    #+#             */
/*   Updated: 2022/11/27 23:23:22 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstringf.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static char	*field_color(t_iobuf *iob, char *ptr)
{
	if (*ptr == 'r')
	{
		iob->field.color = true;
		iob_write(iob, "\33[0;31m", 8);
	}
	else if (*ptr == 'g')
	{
		iob->field.color = true;
		iob_write(iob, "\33[0;32m", 8);
	}
	else if (*ptr == 'y')
	{
		iob->field.color = true;
		iob_write(iob, "\33[0;33m", 8);
	}
	else if (*ptr == 'b')
	{
		iob->field.color = true;
		iob_write(iob, "\33[0;34m", 8);
	}
	if (iob->field.color)
		ptr++;
	return (ptr);
}

static char	*format_field(t_iobuf *iob, char *ptr, va_list *ap)
{
	char	*tmp;
	int		ok;

	ok = 0;
	tmp = field_color(iob, ptr);
	tmp = lf_str_to_uint(tmp, (int *)&iob->field.width);
	if (!tmp)
		return (ptr);
	else if (*tmp == 'd' && ++tmp && ++ok)
		__int(iob, va_arg(*ap, int32_t));
	else if (*tmp == 's' && ++tmp && ++ok)
		__str(iob, va_arg(*ap, char *));
	else if (*tmp == 'c' && ++tmp && ++ok)
		__chr(iob, va_arg(*ap, int));
	else if (*tmp == 'x' && ++tmp && ++ok)
		__hex(iob, va_arg(*ap, uint32_t));
	else if (*tmp == 'p' && ++tmp && ++ok)
		__ptr(iob, va_arg(*ap, uint64_t *));
	if (iob->field.color)
		iob_write(iob, "\33[0m", 4);
	if (ok)
		return (tmp);
	return (iob_write(iob, "%", 1), ptr);
}

void	iob_format_str(t_iobuf *iob, const char *format, va_list *ap)
{
	char	*ptr;

	ptr = (char *)format;
	while (*ptr)
	{
		while (*ptr && *ptr != '%')
			iob_write(iob, ptr++, 1);
		if (!*ptr++)
			break ;
		iob->field.width = 0;
		iob->field.color = 0;
		ptr = format_field(iob, ptr, ap);
	}
}
