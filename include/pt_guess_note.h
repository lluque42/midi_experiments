/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_guess_note.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:02 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 22:43:26 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_guess_note.h
 * This game consist in asking for a random note that the user must press
 * in their keyboard (or any connected midi instrument).
 * The followin options are configurable:
 * 		* Number of miliseconds to timeout.
 * 		* What note naming to use:
 * 			* Latin.
 * 			* Anglo.
 * 			* Both.
 * 		* Include node alterations (sharp, flat, natural).
 * 			* Just naturals.
 * 			* Just naturals and sharps.
 * 			* Just naturals and flats.
 * 			* Naturals, sharps and flats.
 * 				* Naturals may have a sign ("becuadro") or nothing.
 * 		* Whether to include octave number or not.
 *		* Eventually: in a non-C-major scale, number of questions per round,
 *		statistics, etc.
 */

#ifndef PT_GUESS_NOTE_H
# define PT_GUESS_NOTE_H

# include "piano_trainer.h"

/**
 * @enum e_gn_cf_note_naming
 * @brief Base for typedef <b>t_gn_cf_note_naming</b>.
 * @details
 * This type is used to configure the note naming convention for
 * the questions.
 * @var e_gn_cf_note_naming::GN_CF_JUST_LAT_NAMING
 * Latin naming: do, re, mi...
 * @var e_gn_cf_note_naming::GN_CF_JUST_ANG_NAMING
 * Anglosaxon naming: C, D, E...
 * @var e_gn_cf_note_naming::GN_CF_BOTH_NAMING
 * Both conventions.
 * @var e_gn_cf_note_naming::GN_CF_COUNT_NAMING
*/
typedef enum e_gn_cf_note_naming
{
	GN_CF_JUST_LAT_NAMING,
	GN_CF_JUST_ANG_NAMING,
	GN_CF_BOTH_NAMING,
	GN_CF_COUNT_NAMING,
}	t_gn_cf_note_naming;
/**
 * @typedef t_gn_cf_note_naming
 * Based on the @link e_gn_cf_note_naming @endlink enum to indicate
 * the note naming convention to use for the questions.
 */

typedef enum e_gn_cf_alterations
{
	GN_CF_ALTS_NONE,
	GN_CF_ALTS_SHARPS,
	GN_CF_ALTS_FLATS,
	GN_CF_ALTS_BOTH,
	GN_CF_ALTS_BOTH_NAT_SIGN,
	GN_CF_ALTS_COUNT,
}	t_gn_cf_alterations;

typedef struct s_gn_cf
{
	int					timeout_ms;
	int					include_octave;
	int					max_midi_note;
	int					min_midi_note;
	t_gn_cf_note_naming	note_naming;
	t_gn_cf_alterations	alterations;
}	t_gn_cf;

/**
 * @struct s_pt_gn
 * @brief Base for typedef <b>t_pt_gn</b>.
 * @details
 * TODO.
 *
 * @var s_pt_gn::
 */
typedef struct s_pt_gn
{
	t_gn_cf			config;
	int				count;
	t_note_naming	current_note_naming;
	t_note			*ask_note;
	t_note			*guess_note;
	int				rand_note;
	int				rand_alteration;
	int				rand_note_naming;
	int				last_note;
	int				last_octave;
	pthread_mutex_t	note_mx;
	struct s_tmr	*question_tmr;

}	t_pt_gn;
/**
 * @typedef t_pt_gn
 * @brief Based on the @link s_pt_gn @endlink struct.
 */

t_pt_gn	*pt_gn_create_gn(void);

void	pt_gn_destroy_gn(t_pt_gn *gn);

#endif
