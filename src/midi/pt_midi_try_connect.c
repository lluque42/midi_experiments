/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_try_connect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:23:27 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:03:18 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_midi_try_connect(t_pt *pt)
{
	pt->midi->dev_file = pt_files_get_midi_dev_file();
	if (pt->midi->dev_file == NULL)
	{
		dprintf(STDERR_FILENO, "No midi device file was found, ");
		dprintf(STDERR_FILENO, "make sure your keyboard is connected ");
		dprintf(STDERR_FILENO, "and tied to a driver\n");
		return (0);
	}
	pt->midi->dev_fd = open(pt->midi->dev_file, O_RDONLY | O_NONBLOCK);
	if (pt->midi->dev_fd == -1)
		return (perror("opening device file"), 0);
	return (1);
}
