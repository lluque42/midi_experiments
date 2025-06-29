/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gm_guess_note.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:12 by lluque            #+#    #+#             */
/*   Updated: 2025/06/29 11:19:56 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

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
		if (pt->gn->state == GN_ST_STARTING)
		{
			pt->gn->ask_note = pt_gm_get_rand_note(pt);
			pt->gn->guess_result = -1;
			pt_mu_note_print(pt, pt->gn->ask_note);
			if (pt->gn->ask_note == NULL)
				return (0);
			pt->gn->count = pt->gn->config.timeout_ms / 1000;
			pt->gn->question_tmr = pt_tmr_create(pt->gn->config.timeout_ms,
										pt->gn->config.tick_ms,
										pt_gn_tmr_tick_hndlr, (void *)pt,
										pt_gn_tmr_done_hndlr, (void *)pt);
			if (pt->gn->question_tmr == NULL)
				return (0);//////////
			pt->gn->state = GN_ST_ASKING;
			continue ;
		}
		if (pt->gn->state == GN_ST_ASKING)
		{
			pt_gn_render(pt);
			pt_tmr_start(pt->gn->question_tmr, TMR_BLOCK);
			pt->gn->state = GN_ST_CHECKING;
		}
		if (pt->gn->state == GN_ST_CHECKING)
		{
			pthread_mutex_lock(&pt->gn->note_mx);
			if (pt->gn->guess_note == NULL)
			{
				pthread_mutex_unlock(&pt->gn->note_mx);
				pt->gn->guess_result = -2;
				pt->gn->state = GN_ST_SCORING;
				continue ;
			}
			pthread_mutex_unlock(&pt->gn->note_mx);
			if (pt->gn->config.include_octave)
			{
				pthread_mutex_lock(&pt->gn->note_mx);
				if (pt->gn->ask_note->midi == pt->gn->guess_note->midi)
					pt->gn->guess_result = 1;
				else
					pt->gn->guess_result = 0;
				pthread_mutex_unlock(&pt->gn->note_mx);
			}
			else
			{
				if (pt->gn->config.alterations == GN_CF_ALTS_NONE)
				{
					pthread_mutex_lock(&pt->gn->note_mx);
					if (pt->gn->ask_note->chrom == pt->gn->guess_note->chrom)
						pt->gn->guess_result = 1;
					else
						pt->gn->guess_result = 0;
					pthread_mutex_unlock(&pt->gn->note_mx);
				}
				else
				{
					pthread_mutex_lock(&pt->gn->note_mx);
					if (pt->gn->ask_note->pse_diaton == pt->gn->guess_note->pse_diaton)
						pt->gn->guess_result = 1;
					else
						pt->gn->guess_result = 0;
					pthread_mutex_unlock(&pt->gn->note_mx);
				}
			}
			pt->gn->state = GN_ST_SCORING;
		}
		if (pt->gn->state == GN_ST_SCORING)
		{
			pt_gn_render(pt);
			pthread_mutex_lock(&pt->gn->note_mx);
			free(pt->gn->guess_note);
			pt->gn->guess_note = NULL;
			pthread_mutex_unlock(&pt->gn->note_mx);
			free(pt->gn->ask_note);
			pt->gn->ask_note = NULL;
			pt_tmr_destroy(pt->gn->question_tmr);
			pt->gn->question_tmr = NULL;
			sleep(2);
			pt->gn->state = GN_ST_STARTING;
		}
	}
	pt_tmr_destroy(pt->gn->question_tmr);
	pt->gn->question_tmr = NULL;
	pthread_mutex_lock(&pt->gn->note_mx);
	free(pt->gn->guess_note);
	pt->gn->guess_note = NULL;
	pthread_mutex_unlock(&pt->gn->note_mx);
	free(pt->gn->ask_note);
	pt->gn->ask_note = NULL;
	return (1);
}
/*
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
									pt_gn_tmr_tick_hndlr, (void *)pt,
									pt_gn_tmr_done_hndlr, (void *)pt);
//		printf("[pt_gm_guess_note] Debug 2\n");
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
*/
