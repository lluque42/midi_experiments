/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gm_guess_note.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:12 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 23:22:19 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_gn_render(t_pt *pt)
{
	printf("[render] Debug 1\n");
	pthread_mutex_lock(&pt->screen_mx);
	
//	pt_art_print_in_columns(pt, pt->min_ws, 3,
//							pt->gn->current_note_naming, rand_note,
//							pt->alts, rand_alteration,
//							pt->numbers, pt->gn->count);
	pthread_mutex_unlock(&pt->screen_mx);
}

void	tmr_tick_hndlr(void *pt_arg)
{
	return ;
	t_pt	*pt;
	printf("[tick] Debug 1\n");

	pt = (t_pt *)pt_arg;
	pt->gn->count--;
	pt_gn_render(pt);
}

void	tmr_done_hndlr(void *pt_arg)
{
	return ;
	t_pt	*pt;
	printf("[done] Debug 1\n");

	pt = (t_pt *)pt_arg;
	pt_gn_render(pt);
}

int	pt_gm_guess_note(t_pt *pt)
{
	int				rand_note;
	int				rand_alteration;
	int				rand_note_naming;
	t_pt_ascii_art	*current_note_naming;


	pt->gn = calloc(sizeof(t_pt_gn), 1);
	if (pt->gn == NULL)
		return (perror("calloc'ing in guess note"), -1);


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
		rand_note = pt_gm_get_rand_nbr(6, &pt->seed);
		rand_alteration = pt_gm_get_rand_nbr(3, &pt->seed);
		rand_note_naming = pt_gm_get_rand_nbr(0, &pt->seed);
		if (rand_note_naming)
			current_note_naming = pt->ang_notes;
		else
			current_note_naming = pt->lat_notes;
	
	
		//clear the screen before each note
		pt_ui_clear_screen(pt);
		//printf("Try this note: %s\n", latin_notes_sharp[rand_note]);
		
		pt_art_print_in_columns(pt, pt->min_ws, 2,
								current_note_naming, rand_note,
								pt->alts, rand_alteration);
		printf("[pt_gm_guess_note] Debug 1\n");


		pt->gn->count = 5;
//		pt->question_tmr = pt_tmr_create(pt->gn->count * 1000, 1000,
//									tmr_tick_hndlr, (void *)pt,
//									tmr_done_hndlr, (void *)pt);
		printf("[pt_gm_guess_note] Debug 2\n");
		if (pt->question_tmr == NULL)
			return (EXIT_FAILURE);//////////
		pt_tmr_start(pt->question_tmr, TMR_BLOCK);




		pthread_mutex_lock(&pt->note_mx);
		if (pt->last_note == rand_note)
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
		pt->last_note = 0;
		pthread_mutex_unlock(&pt->note_mx);
	}
	return (1);
}
