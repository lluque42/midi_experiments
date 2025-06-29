/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gm_get_rand_note.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:53:33 by lluque            #+#    #+#             */
/*   Updated: 2025/06/26 13:13:04 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_note	*pt_gm_get_rand_note(t_pt *pt)
{
	t_note	*note;
	int		key;

	while (1)
	{
		key = pt->gn->config.max_midi_note - pt->gn->config.min_midi_note;
		key = pt->gn->config.min_midi_note + pt_gm_get_rand_nbr(key, &pt->seed);
		note = pt_mu_create_note_from_midi(key);
		printf("[pt_gm_get_rand_note] Key = %d\n", key);
		if (note == NULL)
			return (NULL);
		if (pt->gn->config.alterations == GN_CF_ALTS_NONE
			&& note->dia_alteration != MU_ALT_NATURAL)
			continue ;
		break ;
	}
	return (note);
}
