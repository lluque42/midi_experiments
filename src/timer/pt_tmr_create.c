/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_tmr_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:06:30 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 20:17:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_tmr	*pt_tmr_create(int duration, int tick,
						timer_hndlr_t tick_hndlr, void *tick_hndlr_arg,
						timer_hndlr_t done_hndlr, void *done_hndlr_arg)
{
	t_tmr	*tmr;

	// Check args consistency
	tmr = calloc(sizeof (t_tmr), 1);
	if (tmr == NULL)
		return (perror("calloc'ing in pt_timer_create()"), NULL);
	tmr->duration = duration;
	tmr->tick = tick;
	tmr->tick_hndlr = tick_hndlr;
	tmr->done_hndlr = done_hndlr;
	tmr->tick_hndlr_arg = tick_hndlr_arg;
	tmr->done_hndlr_arg = done_hndlr_arg;
	pthread_mutex_init(&tmr->blocking_mx, NULL);
	return (tmr);
}
