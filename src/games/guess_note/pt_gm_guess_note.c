/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gm_guess_note.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:12 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 02:09:22 by lluque           ###   ########.fr       */
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

	pt->gn->guess_note = pt_mu_create_note_from_midi(pt->gn->last_note);
	pt_art_print_in_columns(pt, pt->min_ws, 5,
							current_note_naming, pt->gn->rand_note,
							pt->alts, pt->gn->rand_alteration,
							pt->numbers, pt->gn->count,
							current_note_naming, pt->gn->guess_note->pse_diaton,
							pt->alts, pt->gn->guess_note->dia_alteration);
//		pt_art_print_in_columns(pt, pt->min_ws, 2,
//								current_note_naming, rand_note,
//								pt->alts, rand_alteration);
}

void	tmr_tick_hndlr(void *pt_arg)
{
	t_pt	*pt;
	printf("[tick] Debug 1\n");

	pt = (t_pt *)pt_arg;
	pt->gn->count--;
	pt_gn_render(pt);
}

void	tmr_done_hndlr(void *pt_arg)
{
	t_pt	*pt;
	printf("[done] Debug 1\n");

	pt = (t_pt *)pt_arg;
	pt_gn_render(pt);
}

int	pt_gm_guess_note(t_pt *pt)
{
//	int				rand_note;				// 0-11
//	int				rand_alteration;		// flat or sharps
//	int				rand_note_naming;		// lat or ang




/*

//2212221 = 12 (major scale)


	pt_art_print_in_columns(pt, pt->min_ws, 1,
							pt->numbers, 1);
	pt_art_print_in_columns(pt, pt->min_ws, 1,
							pt->alts, 1);
	pt_art_print_in_columns(pt, pt->min_ws, 1,
							pt->lat_notes, 1);
	pt_art_print_in_columns(pt, pt->min_ws, 1,
							pt->ang_notes, 1);
	pt_art_print_in_columns(pt, pt->min_ws, 4,
							pt->numbers, 1,
							pt->alts, 2,
							pt->lat_notes, 3,
							pt->ang_notes, 4);
	pt_art_print_dump(pt, pt->alts);
*/
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
	
	
		//clear the screen before each note
		pt_ui_clear_screen(pt);
		//printf("Try this note: %s\n", latin_notes_sharp[rand_note]);
		
//		pt_art_print_in_columns(pt, pt->min_ws, 2,
//								current_note_naming, rand_note,
//								pt->alts, rand_alteration);
		printf("[pt_gm_guess_note] Debug 1\n");


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
