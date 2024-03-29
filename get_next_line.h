/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 14:34:51 by tberthie          #+#    #+#             */
/*   Updated: 2016/11/22 17:29:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 32

typedef struct		s_slot
{
	char			*save;
	int				fd;
	struct s_slot	*next;
}					t_slot;

int					get_next_line(const int fd, char **line);

#endif
