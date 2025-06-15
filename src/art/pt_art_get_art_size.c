/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_art_get_art_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:49:21 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 11:08:22 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

struct winsize	pt_art_get_art_size(char *path)
{
	int				fd;
	struct winsize	ws;
	char			*line;
	int				rows;
	int				cols;

	ws.ws_row = 0;
	ws.ws_col = 0;
	rows = 0;
	cols = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror(path), ws);
	line = ft_gnl(fd);
	cols = strlen(line);
	while (line != NULL)
	{
		rows++;
		free(line);
		line = ft_gnl(fd);
		if (line != NULL && strlen(line) != (unsigned)cols)
		{
			dprintf(STDERR_FILENO, "Inconsistent columns number (%s)\n", path);
			return (close(fd), ws);
		}
	}
	ws.ws_row = rows;
	ws.ws_col = cols - 1;
	close(fd);
	return (ws);
}
