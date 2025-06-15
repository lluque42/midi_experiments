/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piano_trainer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 12:15:35 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file piano_trainer.h
 * The program main header file that include every other header to simplify
 * the references in the code files.
 */

#ifndef PIANO_TRAINER_H
# define PIANO_TRAINER_H

# include <sys/types.h>	// dir related functions stdlib
# include <dirent.h>	// dir related functions stdlib
# include <stdio.h>		// perror()
# include <errno.h>
# include <dirent.h>	// readdir()
# include <stdlib.h>	// getenv()
# include <string.h>
# include <fcntl.h>		// open() flags, modes
# include <unistd.h>	// read(), sleep(), some terminal related functions
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>	// gettimeofday()
# include <termcap.h>	// UI terminal related functions
# include <termios.h>	// UI terminal related functions
# include <sys/ioctl.h>	// UI terminal related functions ioctl()
# include <math.h>		// ceil()
# include <stdarg.h>	// variadic functions
# include "pt_type.h"
# include "pt_files.h"
# include "pt_midi.h"
# include "pt_ui.h"
# include "pt_timer.h"
# include "pt_sig.h"
# include "pt_ascii_art.h"
# include "libft.h"

#endif
