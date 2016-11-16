/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 14:34:43 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/17 00:34:34 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int	create_save(t_save *save, int fd)
{
	int		i;
	char	**buff;
	int		*fdt;
	char	*new;

	i = save->size;
	while (i--)
		if (save->fd[i] == fd)
			return (i);
	if (!(buff = malloc(sizeof(char*) * (save->size + 1))) ||
	!(fdt = malloc(sizeof(save->fd) + sizeof(int))) ||
	!(new = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (i++ < save->size - 1)
	{
		if (!(buff[i] = ft_strdup(save->buff[i])))
			return (-1);
		fdt[i] = save->fd[i];
	}
	buff[save->size] = new;
	fdt[save->size] = fd;
	save->fd = fdt;
	save->buff = buff;
	return (save->size++);
}

int			get_next_line(const int fd, char **line)
{
	static t_save	*save;
	int				slot;
	int				rd;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;

	if ((!save && !(save = malloc(sizeof(t_save*)))) ||
	(slot = create_save(save, fd)) == -1)
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)))
	{
		if (rd == -1 || !(tmp = ft_strnew(rd +
		ft_strlen(save->buff[slot]))))
			return (-1);
		buff[rd] = '\0';
		if (*save->buff[slot])
			tmp = ft_strcpy(tmp, save->buff[slot]);
		tmp = ft_strcat(tmp, buff);
		save->buff[slot] = ft_strdup(tmp);
	}
	tmp = ft_strdup(save->buff[slot]);
	if (ft_strchr(save->buff[slot], '\n'))
	{
		*ft_strchr(tmp, '\n') = '\0';
		save->buff[slot] = ft_strcpy(save->buff[slot],
		ft_strchr(save->buff[slot], '\n') + 1);
	}
	else
		*save->buff[slot] = '\0';
	*line = ft_strdup(tmp);
	return (*tmp ? 1 : 0);
}
