/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gn_create_gn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:14:33 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 23:22:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt_gn	*pt_gn_create_gn(void)
{
	t_pt_gn	*gn;

	gn = ft_calloc(sizeof(t_pt_gn), 1);
	if (gn == NULL)
		return (perror("Calloc'ing gn"), NULL);
	pthread_mutex_init(&gn->note_mx, NULL);
	gn->config.timeout_ms = 5000;
	gn->config.include_octave = 0;
	gn->config.max_midi_note = 21;	// My 88 keys keyboard
	gn->config.min_midi_note = 108;	// My 88 keys keyboard 
	gn->config.note_naming = GN_CF_JUST_LAT_NAMING;
	gn->config.alterations = GN_CF_ALTS_BOTH;
	gn->guess_note = pt_mu_create_note_from_midi(0);
//	gn->ask_note = calloc(sizeof(t_note), 1);
//	if (gn->ask_note == NULL)
//		return (perror("calloc'ing note"), NULL); // free more
//	gn->guess_note = calloc(sizeof(t_note), 1);
//	if (gn->guess_note == NULL)
//		return (perror("calloc'ing note"), NULL); // free more
	return (gn);
}
