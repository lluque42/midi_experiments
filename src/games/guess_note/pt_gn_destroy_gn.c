/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gn_destroy_gn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:17:34 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 02:21:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_gn_destroy_gn(t_pt_gn *gn)
{
	pthread_mutex_destroy(&gn->note_mx);
	free(gn->guess_note);
	free(gn->ask_note);
	//pt_timer_destroy(gn->question_tmr);	///////////////////////////
	free(gn);
}
