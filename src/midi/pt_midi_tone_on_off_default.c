/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_tone_on_off_default.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:49:06 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 22:47:08 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_midi_tone_on_off_default(void *pt_arg, void *midi_data)
{
	t_pt_midi_tone_msg	tone_msg;
	t_note				*note;
	char				*note_name[] = {"do","re","mi","fa","sol","la","si"};
	char				*note_alt[] = {"","#","b", "nat"};
	t_pt				*pt;

	pt = (t_pt *)pt_arg;
	tone_msg = *((t_pt_midi_tone_msg *)midi_data);
	note = pt_mu_create_note_from_midi(tone_msg.key);
	pthread_mutex_lock(&pt->screen_mx);
	if (tone_msg.status == MIDI_TONE_OFF)
		printf("Channel '%d' just released ", tone_msg.channel);
	else
		printf("Channel '%d' just pressed ", tone_msg.channel);
	printf("the '%s%s' (semitone %d in octave) ",
			note_name[note->pse_diaton], note_alt[note->dia_alteration],
			note->chrom);
	printf("in the '%d' octave with '%d' velocity. (midi note value = %d)\n",
			note->octave, tone_msg.vel, tone_msg.key);
	pthread_mutex_unlock(&pt->screen_mx);
	free(note);
}
