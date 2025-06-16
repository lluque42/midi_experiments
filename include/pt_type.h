/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:14:27 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:22:50 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_type.h
 * Definitions and prototypes related to the program main control struct
 */

#ifndef PT_TYPE_H
# define PT_TYPE_H

// Forward declaration
//typedef struct s_tmr			t_tmr;
//typedef struct s_pt_ascii_art	t_pt_ascii_art;
//typedef struct s_pt_gn			t_pt_gn;

/**
 * @struct s_pt
 * @brief Base for typedef <b>t_pt</b>.
 * @details
 * TODO.
 *
 * @var s_pt::seed
 * TODO.
 *
 * @var s_pt::exit_pending
 * A flag to let every thread knows that the program is exiting and that
 * they must wrap things up.
 *
 * @var s_pt::flags_mx
 * A mutex for flags (e.g. exit_pending).
 *
 * @var s_pt::last_note
 * TODO.
 *
 * @var s_pt::last_octave
 * TODO.
 *
 * @var s_pt::note_mx
 * TODO.
 *
 * @var s_pt::termios_orig
 * The tcgetattr()/tcsetattr() termios struct with the original unchanged
 * terminal configurations to be restored when the program exits.
 *
 * @var s_pt::env_termtype
 * The value of the environment variable TERM as returned by getenv().
 *
 * @var s_pt::term_buffer
 * The termcap terminal description that matches env_termtype (TERM)
 * as returned by tgetent().
 *
 * @var s_pt::ws
 * Termios (ioctl) winsize initialized at startup and updated
 * on SIGWINCH signal.
 */
typedef struct s_pt
{
	struct s_pt_midi		*midi;
	struct s_pt_gn  		*gn;
	unsigned int			seed;
	int						exit_pending;
	pthread_mutex_t			flags_mx;
	struct termios			termios_orig;
	char					*env_termtype;
	//char					term_buffer[2048];	// For UNIX, didn't free ok
	char					*term_buffer;
	struct winsize			min_ws;	// Calculated from the logo ascii art
	struct winsize			ws;
	pthread_mutex_t			ws_mx;
	pthread_mutex_t			screen_mx;
	struct s_pt_ascii_art	*logo;
	struct s_pt_ascii_art	*alts;
	struct s_pt_ascii_art	*lat_notes;
	struct s_pt_ascii_art	*ang_notes;
	struct s_pt_ascii_art	*numbers;
}	t_pt;
/**
 * @typedef t_pt
 * @brief Based on the @link s_pt @endlink struct.
 */

# ifndef PT_GLOBAL_VAR
#  define PT_GLOBAL_VAR

extern t_pt	*pt;

# endif

t_pt	*pt_create_pt(void);

void	pt_destroy_pt(t_pt *pt);

#endif
