/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_destroy_pt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:55:42 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:18:33 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_destroy_pt(t_pt *pt)
{
	pthread_mutex_destroy(&pt->flags_mx);
	pthread_mutex_destroy(&pt->ws_mx);
	pthread_mutex_destroy(&pt->screen_mx);
	free(pt->env_termtype);
	pt_midi_destroy_midi(pt->midi);
	pt_gn_destroy_gn(pt->gn);
	pt_art_destroy_art(pt->logo);
	pt_art_destroy_art(pt->alts);
	pt_art_destroy_art(pt->lat_notes);
	pt_art_destroy_art(pt->ang_notes);
	pt_art_destroy_art(pt->numbers);
	free(pt);
}
