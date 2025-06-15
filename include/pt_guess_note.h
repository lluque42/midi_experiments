/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_guess_note.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:02 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 22:05:39 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_guess_note.h
 * TODO.
 */

#ifndef PT_GUESS_NOTE_H
# define PT_GUESS_NOTE_H

# include "piano_trainer.h"

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
	int				count;
	t_note_naming	current_note_naming;
	t_note			ask_note;
	t_note			guess_note;
}	t_pt_gn;
/**
 * @typedef t_pt_gn
 * @brief Based on the @link s_pt_gn @endlink struct.
 */

#endif
