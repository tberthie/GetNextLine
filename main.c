/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:16:41 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/16 18:53:39 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	int		fd;
	char	**line;

	if (ac != 2)
		return (0);
	fd = open(av[1] ,O_RDONLY);
	line = NULL;
	printf("%d\n%s\n", get_next_line(fd, line), *line);
	return (0);
}
