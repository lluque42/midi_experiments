/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gn_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:08:13 by lluque            #+#    #+#             */
/*   Updated: 2025/07/26 10:41:00 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_gn_render(t_pt *pt)
{
	t_pt_ascii_art	*current_note_naming;



	pt->gn->rand_note_naming = 1;
	if (pt->gn->rand_note_naming)
		pt->gn->current_note_naming = MU_NN_LAT;
	else
		pt->gn->current_note_naming = MU_NN_ANG;



	if (pt->gn->current_note_naming == MU_NN_LAT)
		current_note_naming = pt->lat_notes;
	else
		current_note_naming = pt->ang_notes;

	pt_ui_clear_screen(pt);

	char	*header = "      PRESS:                           TIME LEFT:                 YOUR GUESS:  \n";
	char	*ok_footer = "CORRECT!!! \n";
	char	*wrong_footer = "WRONG, TRY AGAIN! \n";
	char	*timeout_footer = "TIME OUT! A LITTLE QUICKER NEXT TIME! \n";

	pthread_mutex_lock(&pt->screen_mx);
	write(STDOUT_FILENO, header, strlen(header));
	pthread_mutex_unlock(&pt->screen_mx);

	// BUG! Segfault when piano key is pressed during second 0
	//printf("[pt_gn_render] pt->alts=%p pt->gn->ask_note->dia_alteration=%d\n", pt->alts, pt->gn->ask_note->dia_alteration);
	printf("[pt_gn_render] pt->alts=%p\n", pt->alts);
	printf("[pt_gn_render] pt->gn->ask_note->dia_alteration=%d\n", pt->gn->ask_note->dia_alteration);
	if (pt->gn->guess_note != NULL)
	{
		pt_art_print_in_columns(pt, pt->min_ws, 5,
								current_note_naming, pt->gn->ask_note->pse_diaton,
								pt->alts, pt->gn->ask_note->dia_alteration,
								pt->numbers, pt->gn->count,
								current_note_naming, pt->gn->guess_note->pse_diaton,
								pt->alts, pt->gn->guess_note->dia_alteration);
	}
	else
	{
		pt_art_print_in_columns(pt, pt->min_ws, 5,
								current_note_naming, pt->gn->ask_note->pse_diaton,
								pt->alts, pt->gn->ask_note->dia_alteration,
								pt->numbers, pt->gn->count,
								pt->q_mark, 0,
								pt->q_mark, 0);

	}
	pthread_mutex_lock(&pt->screen_mx);
	if (pt->gn->guess_result == 1)
		write(STDOUT_FILENO, ok_footer, strlen(ok_footer));
	if (pt->gn->guess_result == 0)
		write(STDOUT_FILENO, wrong_footer, strlen(wrong_footer));
	if (pt->gn->guess_result == -2)
		write(STDOUT_FILENO, timeout_footer, strlen(timeout_footer));
	pthread_mutex_unlock(&pt->screen_mx);
}

