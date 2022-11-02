/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_mem_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:56:49 by nmathieu          #+#    #+#             */
/*   Updated: 2022/11/02 10:48:51 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	mem_set(void *p, char byte, size_t n)
{
	while (n)
	{
		*(char *)p = byte;
		n--;
		p++;
	}
}
