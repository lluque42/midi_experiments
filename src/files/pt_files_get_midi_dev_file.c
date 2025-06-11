/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_files_get_midi_dev_file.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:37:35 by lluque            #+#    #+#             */
/*   Updated: 2025/06/11 12:39:17 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

char	*pt_files_get_midi_dev_file(void)
{
	char			*try_dir;
	DIR				*dev_snd;

	try_dir = ALSA_DEV_FILES_BASE_DIR;
	dev_snd = opendir(try_dir);
	if (dev_snd == NULL)
	{
		printf("No ALSA device file directory found (%s), trying for OSS...\n",
				try_dir);
		try_dir = OSS_DEV_FILES_BASE_DIR;
		dev_snd = opendir(try_dir);
		if (dev_snd == NULL)
			return (printf("No OSS device file directory found (%s)...\n",
						try_dir), NULL);
	}
	printf("A directory for sound device files was found (%s)..\n", try_dir);
	return (pt_files_try_dir_items(dev_snd, try_dir));
}
