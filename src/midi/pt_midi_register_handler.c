/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_register_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:54:44 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 19:43:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_midi_register_handler(t_pt_midi *midi,
			t_midi_status_msg_type msg_type, midi_hndlr_t hndlr)
{
	if (msg_type == MIDI_TONE_OFF)
		midi->on_tone_off = hndlr;
	else if (msg_type == MIDI_TONE_ON)
		midi->on_tone_on = hndlr;
}
