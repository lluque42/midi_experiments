/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_music.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:02 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 21:43:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_music.h
 * TODO.
 */

#ifndef PT_MUSIC_H
# define PT_MUSIC_H

// For my 88 keys keyboard, the middle C is in the 4th octave,
// so the key 60 is C4 (do4).
# define PT_MIDI_60_MIDDLE_C_OCTAVE 4

# define MAJ_SCALE "2212221"

# include "piano_trainer.h"

/**
 * @enum e_note_naming
 * @brief Base for typedef <b>t_note_naming</b>.
 * @details This type is used to indicate the note naming convention.
 * @var e_note_naming::MU_NN_LAT
 * Latin naming: do, re, mi...
 * @var e_note_naming::MU_NN_ANG
 * Anglosaxon naming: C, D, E...
*/
typedef enum e_note_naming
{
	MU_NN_LAT,
	MU_NN_ANG,
}	t_note_naming;
/**
 * @typedef t_note_naming
 * Based on the @link e_note_naming @endlink enum to indicate
 * the note naming convention.
 */

/**
 * @enum e_note_alteration
 * @brief Base for typedef <b>t_note_alteration</b>.
 * @details This type is used to indicate the note alteration.
 * @var e_note_alteration::MU_ALT_NA
 * Not indicated.
 * @var e_note_alteration::MU_ALT_SHARP
 * Sharp (one semitone above).
 * @var e_note_alteration::MU_ALT_FLAT
 * Flat (one semitone below).
 * @var e_note_alteration::MU_ALT_NATURAL
 * Natural (same as in scale).
*/
typedef enum e_note_alteration
{
	MU_ALT_NA,
	MU_ALT_SHARP,
	MU_ALT_FLAT,
	MU_ALT_NATURAL,
}	t_note_alteration;
/**
 * @typedef t_note_alteration
 * Based on the @link e_note_alteration @endlink enum to indicate
 * the note alteration.
 */

/**
 * @struct s_note
 * @brief Base for typedef <b>t_note</b>.
 * @details
 * An struct to characterize a note in several useful notation types.
 * @var s_note::midi
 * The absolute midi value if received from a keyboard.
 * Theoretically it could be anything from 0 to 127.
 * @var s_note::octave
 * The octave (see define PT_MIDI_60_MIDDLE_C_OCTAVE).
 * @var s_note::chrom
 * The chromatic interval of this note from the C note of it same octave.
 * A C = 0, C# = 1, D = 2... B = 11.
 * @var s_note::pse_diaton
 * The position in the C major escale in a diatonic sense (but starting at 0).
 * For example C = 0, D = 1, E = 2... B = 6. It's complemented with the
 * value of dia_alteration.
 * @var s_note::dia_alteration
 * A value of 0 if no alteration. A value of 1 for a semi-tone above the
 * value of s_note::pse_diaton
 */
typedef struct s_note
{
	int					midi;
	int					octave;
	int					chrom;
	int					pse_diaton;
	t_note_alteration	dia_alteration;
}	t_note;
/**
 * @typedef t_note
 * @brief Based on the @link s_note @endlink struct.
 */

void	pt_mu_note_print(t_pt *pt, t_note *note);

// Midi key value (actually note value) is in the range: 0 to 127.
// Must be freed with free().
t_note	*pt_mu_create_note_from_midi(int midi_key_value);

// Chrom refers to chromatic. Best word I thought for a number between
// 0 and 11 which in a chromatic scale points to do-si (C-B)
// Must be freed with free().
t_note  *pt_mu_create_note_from_chrom(int chrom);

#endif
