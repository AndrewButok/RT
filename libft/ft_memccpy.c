/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:08:10 by abutok            #+#    #+#             */
/*   Updated: 2019/06/21 22:14:50 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*md;
	unsigned char	*ms;
	unsigned char	ch;
	size_t			i;

	md = (unsigned char*)dst;
	ms = (unsigned char*)src;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		md[i] = ms[i];
		if (md[i] == ch)
			return (&md[i + 1]);
		i++;
	}
	return (NULL);
}
