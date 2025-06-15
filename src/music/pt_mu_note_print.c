/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_mu_note_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:43:19 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 00:08:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_mu_note_print(t_pt *pt, t_note *note)
{
	pthread_mutex_lock(&pt->screen_mx);
	printf("note->midi = %d\n", note->midi);
	printf("note->octave = %d\n", note->octave);
	printf("note->chrom = %d\n", note->chrom);
	printf("note->pse_diaton = %d\n", note->pse_diaton);
	printf("note->dia_alteration = %d\n", note->dia_alteration);
	pthread_mutex_unlock(&pt->screen_mx);
}
