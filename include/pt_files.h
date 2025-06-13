/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_files.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/12 11:21:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_files.h
 * TODO.
 */

#ifndef PT_FILES_H
# define PT_FILES_H

# include "piano_trainer.h"

// Advanced Linux Sound Architecture, the new aproach
# define ALSA_DEV_FILES_BASE_DIR "/dev/snd/"

// Open Sound System, legacy
# define OSS_DEV_FILES_BASE_DIR "/dev/dsp/"

char	*pt_files_get_midi_dev_file(void);

char	*pt_files_try_dir_items(DIR *dev_snd, char *try_dir);

#endif
