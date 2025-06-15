/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_art_load_art.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:49:21 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 20:06:55 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt_ascii_art	*pt_art_load_art(char *path, int ver_el, int hor_el)
{
	t_pt_ascii_art	*art;
	int				fd;
	int				index;
	char			*line;

	art = calloc(sizeof(t_pt_ascii_art), 1);
	if (art == NULL)
		return (perror("calloc'ing art"), NULL);
	art->ver_el = ver_el;
	art->hor_el = hor_el;
	art->size = pt_art_get_art_size(path);
	if (art->size.ws_row == 0 || art->size.ws_col == 0)
		return (free(art), dprintf(STDERR_FILENO, "invalid size in art"), NULL);
	art->data = malloc(sizeof(char) * art->size.ws_row * (art->size.ws_col + 1));
	if (art->data == NULL)
		return (free(art), dprintf(STDERR_FILENO, "invalid size in art"), NULL);
	index = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(art->data), free(art), perror("opening art"), NULL);
	line = ft_gnl(fd);
	while (line != NULL)
	{
		memcpy(art->data + index, line, art->size.ws_col);
		free(line);
		index += art->size.ws_col;
		line = ft_gnl(fd);
	}
	return (art);
}
