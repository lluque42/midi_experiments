/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_files_try_dir_items.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:37:35 by lluque            #+#    #+#             */
/*   Updated: 2025/06/12 11:48:17 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

char	*pt_files_try_dir_items(DIR *dev_snd, char *try_dir)
{
	struct dirent	*current_dir_entry;
	char			*midi_dev_file;

	midi_dev_file = NULL;
	current_dir_entry = readdir(dev_snd);
	for (current_dir_entry = readdir(dev_snd);
			current_dir_entry != NULL; current_dir_entry = readdir(dev_snd))
	{
		if (ft_strncmp(current_dir_entry->d_name, "midi", 4) != 0)
			continue ;
		if (current_dir_entry->d_type == DT_UNKNOWN)
		{
			//try with lstat
		}
		else if (current_dir_entry->d_type == DT_CHR)
		{
			midi_dev_file = calloc(sizeof (char),
					strlen(try_dir) + strlen(current_dir_entry->d_name) + 1);
			if (midi_dev_file == NULL)
				return (perror(""), closedir(dev_snd), NULL);
			memcpy(midi_dev_file, try_dir, strlen(try_dir));
			memcpy(midi_dev_file + strlen(try_dir), current_dir_entry->d_name,
					strlen(current_dir_entry->d_name));
		}
	}
	closedir(dev_snd);
	return (midi_dev_file);
}
