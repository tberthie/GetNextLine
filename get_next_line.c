/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 14:34:43 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/18 17:03:11 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_slot	*get_slot(t_slot *first, int fd)
{
	t_slot	*slot;

	slot = first;
	while (slot && slot->fd != fd)
		slot = slot->next;
	if (!slot)
	{
		if (!(slot = malloc(sizeof(t_slot*))))
			return (0);
		slot->fd = fd;
		slot->save = ft_strnew(0);
		slot->next = NULL;
		while (first && first->next)
			first = first->next;
		if (first)
			first->next = slot;
	}
	return (slot);
}

static int		process_slot(t_slot *slot, char **line)
{
	char	*tmp;

	*line = "";
	if (*(slot->save++) == '\n')
		return (1);
	slot->save--;
	if (!(tmp = ft_strdup(slot->save)))
		return (-1);
	slot->save = ft_strchr(tmp, '\n') ? ft_strchr(slot->save, '\n') + 1 :
	&(slot->save[ft_strlen(slot->save)]);
	if (ft_strchr(tmp, '\n'))
		*ft_strchr(tmp, '\n') = '\0';
	if (!(*line = ft_strdup(tmp)))
		return (-1);
	return (*tmp ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_slot	*first;
	t_slot			*slot;
	int				rd;
	char			buff[BUFF_SIZE];
	char			*tmp;

	if (!line || !(slot = get_slot(first, fd)))
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)))
	{
		if (rd == -1 || !(tmp = ft_strnew(rd + ft_strlen(slot->save))))
			return (-1);
		first = first ? first : slot;
		tmp = ft_strncat(ft_strcpy(tmp, slot->save), buff, rd);
		slot->save = ft_strdup(tmp);
		free(tmp);
	}
	return (process_slot(slot, line));
}
