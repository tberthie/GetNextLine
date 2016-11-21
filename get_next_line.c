/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:42:16 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/21 16:42:32 by tberthie         ###   ########.fr       */
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
		if (!(slot = (t_slot*)malloc(sizeof(t_slot*))))
			return (0);
		slot->fd = fd;
		slot->next = 0;
		slot->save = 0;
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
	int		ret;

	if (!(*line = ft_strnew(1)))
		return (-1);
	if (*slot->save == '\n')
	{
		if (!(tmp = ft_strdup(slot->save + 1)))
			return (-1);
		free(slot->save);
		slot->save = tmp;
		return (1);
	}
	if (!(tmp = ft_strdup(slot->save)))
		return (-1);
	free(slot->save);
	slot->save = ft_strchr(tmp, '\n') ? ft_strdup(ft_strchr(tmp, '\n') + 1) : 0;
	if (ft_strchr(tmp, '\n'))
		*ft_strchr(tmp, '\n') = '\0';
	free(*line);
	if (!(*line = ft_strdup(tmp)))
		return (-1);
	ret = *tmp ? 1 : 0;
	free(tmp);
	return (ret);
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
	first = first ? first : slot;
	while ((rd = read(fd, buff, BUFF_SIZE)))
	{
		if (rd == -1 || !(tmp = ft_strnew(rd + ft_strlen(slot->save))))
			return (-1);
		tmp = ft_strncat(ft_strcpy(tmp, slot->save), buff, rd);
		if (slot->save)
			free(slot->save);
		slot->save = tmp;
		if (ft_strchr(slot->save, '\n'))
			return (process_slot(slot, line));
	}
	return (process_slot(slot, line));
}
