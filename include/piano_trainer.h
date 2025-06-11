/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piano_trainer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/11 23:07:34 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIANO_TRAINER_H
# define PIANO_TRAINER_H

# include <sys/types.h>	// dir related functions stdlib
# include <dirent.h>	// dir related functions stdlib
# include <stdio.h>		// perror()
# include <errno.h>
# include <dirent.h>	// readdir()
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>		// open() flags, modes
# include <unistd.h>	// read(), sleep()
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>	// gettimeofday()
# include "pt_files.h"
# include "pt_midi.h"
# include "libft.h"

typedef struct s_pt
{
	char			*midi_dev_file;
	int				dev_fd;
	pthread_t		listener_thread;
	unsigned int	seed;
	int				exit_pending;
	pthread_mutex_t	flags_mx;
	int				last_note;
	int				last_octave;
	pthread_mutex_t	note_mx;
}	t_pt;

# ifndef PT_GLOBAL_VAR
#  define PT_GLOBAL_VAR

extern t_pt	*pt;

# endif

t_pt	*pt_create_pt(void);

void	pt_destroy_pt(t_pt *pt);

#endif
