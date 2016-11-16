/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 14:34:43 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/16 19:20:49 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

t_save		*create_save(t_save *save, int fd)
{
	int		i;
	char	*buff;
	int		*fdt;
	char	*new;

	i = save->size;
	while (i--)
		if (save->fd[i] == fd)
			return (i);
	if (!(buff = malloc(sizeof(save->buff) + sizeof(char) *
	(BUFF_SIZE + 1))) || !(fdt = malloc(sizeof(save->fd) + sizeof(int))) ||
	!(new = ft_strnew(BUFF_SIZE)))
		return (-1);
	/* BUFF > buff[BUFFSIZE + 1] = fd partition
	while (i++ < save->size - 1)
	{
		if (!(buff[i] = ft_strcpy(&buff[(BUFF_SIZE + 1) * (i - 1)]),save->buff[i]))
			return (-1);
		fdt[i] = save->fd[i];
	}
	buff[save->size] = new;
	fdt[save->size] = fd;
	save->fd = fdt;
	save->buff = buff;
	return (save->size++);
	*/
}

int			get_next_line(const int fd, char **line)
{
	static t_save	*save;
	int				slot;
	int				rd;
	char			buff[BUFF_SIZE];
	char			*tmp;

	if (!save && (!(save = malloc(sizeof(t_save*))) ||
	!(slot = create_save(save, fd))))
		return (-1);
	ft_putstr("A\n");
	printf("%d\n", sizeof(save));
	while ((rd = read(fd, buff, BUFF_SIZE)) && 
	!ft_strchr(save->buff[slot], '\n'))
	{
		ft_putstr("A\n");
		if (rd == -1 || !(tmp = ft_strnew(rd +
		ft_strlen(save->buff[slot]))))
			return (-1);
		ft_putstr("B\n");
		if (*save->buff[slot])
			tmp = ft_strcpy(tmp, save->buff[slot]);
		printf("\n%s\n", tmp);
		ft_putstr("C\n");
		save->buff[slot] = ft_strncat(save->buff[slot], buff, rd);
	}
	printf("%s\n", save->buff[slot]);
	return (rd ? 1 : 0);
}
