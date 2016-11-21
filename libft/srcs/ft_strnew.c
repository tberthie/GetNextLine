/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:06:37 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/21 13:30:57 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i <= (int)size)
		new[i++] = '\0';
	return (new);
}
