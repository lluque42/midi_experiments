/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gn_midi_hndlrs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:06:08 by lluque            #+#    #+#             */
/*   Updated: 2025/06/26 22:06:37 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void    pt_gn_tone_on_hndlr(void *pt_arg, void *midi_data)
{
	t_pt_midi_tone_msg	tone_msg;
	t_note				*note;
	t_pt				*pt;

	pt = (t_pt *)pt_arg;
	tone_msg = *((t_pt_midi_tone_msg *)midi_data);
	note = pt_mu_create_note_from_midi(tone_msg.key);
	pthread_mutex_lock(&pt->gn->note_mx);
	free(pt->gn->guess_note);
	pt->gn->guess_note = note;
	pt_mu_note_print(pt, pt->gn->guess_note);
	pthread_mutex_unlock(&pt->gn->note_mx);
	pt_gn_render(pt);
}

void    pt_gn_tone_off_hndlr(void *pt_arg, void *midi_data)
{
	// Do nothing, warn nothing
	if (pt_arg || midi_data)
		return ;
	return ;
}
