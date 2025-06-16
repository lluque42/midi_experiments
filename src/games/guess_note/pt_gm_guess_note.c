/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gm_guess_note.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:12 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 23:29:29 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_gn_render(t_pt *pt)
{
	t_pt_ascii_art	*current_note_naming;

	if (pt->gn->current_note_naming == MU_NN_LAT)
		current_note_naming = pt->lat_notes;
	else
		current_note_naming = pt->ang_notes;

	pt_ui_clear_screen(pt);

	pt_art_print_in_columns(pt, pt->min_ws, 5,
							current_note_naming, pt->gn->rand_note,
							pt->alts, pt->gn->rand_alteration,
							pt->numbers, pt->gn->count,
							current_note_naming, pt->gn->guess_note->pse_diaton,
							pt->alts, pt->gn->guess_note->dia_alteration);
}

void	tmr_tick_hndlr(void *pt_arg)
{
	t_pt	*pt;
	printf("[tick] Debug 1\n");
	// There was a disable somewhere that worked at least to prevent leaks.
	pt = (t_pt *)pt_arg;
	pt->gn->count--;
	pt_gn_render(pt);
}

void	tmr_done_hndlr(void *pt_arg)
{
	t_pt	*pt;
	printf("[done] Debug 1\n");
	// There was a disable somewhere that worked at least to prevent leaks.
	pt = (t_pt *)pt_arg;
	pt_gn_render(pt);
}

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

int	pt_gm_guess_note(t_pt *pt)
{
	pt_midi_register_handler(pt->midi, MIDI_TONE_OFF, pt_gn_tone_off_hndlr);
	pt_midi_register_handler(pt->midi, MIDI_TONE_ON, pt_gn_tone_on_hndlr);

	while (1)
	{
		pthread_mutex_lock(&pt->flags_mx);
		if (pt->exit_pending)
		{
			pthread_mutex_unlock(&pt->flags_mx);
			break ;
		}
		pthread_mutex_unlock(&pt->flags_mx);



		pt->gn->rand_note = pt_gm_get_rand_nbr(6, &pt->seed);
		pt->gn->rand_alteration = pt_gm_get_rand_nbr(3, &pt->seed);
		//pt->gn->rand_note_naming = pt_gm_get_rand_nbr(0, &pt->seed);
		pt->gn->rand_note_naming = 1;
		if (pt->gn->rand_note_naming)
			pt->gn->current_note_naming = MU_NN_LAT;
		else
			pt->gn->current_note_naming = MU_NN_ANG;
	
	

		pt_gn_render(pt);



		pt->gn->count = 5;
		pt->gn->question_tmr = pt_tmr_create(pt->gn->count * 1000, 1000,
									tmr_tick_hndlr, (void *)pt,
									tmr_done_hndlr, (void *)pt);
		printf("[pt_gm_guess_note] Debug 2\n");
		if (pt->gn->question_tmr == NULL)
			return (EXIT_FAILURE);//////////
		pt_tmr_start(pt->gn->question_tmr, TMR_BLOCK);




		pthread_mutex_lock(&pt->gn->note_mx);
		if (pt->gn->last_note == pt->gn->rand_note)
		{
			pthread_mutex_lock(&pt->screen_mx);
			printf ("Well done!!!!\n");
			pthread_mutex_unlock(&pt->screen_mx);
		}
		else
		{
			pthread_mutex_lock(&pt->screen_mx);
			printf ("Wrong!\n");
			pthread_mutex_unlock(&pt->screen_mx);
		}
		pthread_mutex_lock(&pt->screen_mx);
//		printf("You pressed: %s%d\n", latin_notes_sharp[pt->last_note],
//				pt->last_octave);
		pthread_mutex_unlock(&pt->screen_mx);
		pt->gn->last_note = 0;
		pthread_mutex_unlock(&pt->gn->note_mx);
	}
	return (1);
}
