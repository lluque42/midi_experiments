/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_tmr_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:13:31 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:41:20 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_tmr_start(t_tmr *tmr, t_tmr_block block)
{
	if (tmr == NULL)
		return (0);
	if (pthread_create(&tmr->counter_thread, NULL, &pt_tmr_counter, tmr))
		return (perror("launching tmr counter thread"), 0);
	if (pthread_detach(tmr->counter_thread) != 0)
		return (perror("dettaching tmr counter thread"), 0);
	usleep(200);
	if (block == TMR_BLOCK)
	{
		tmr->blocks = TMR_BLOCK;
		pthread_mutex_lock(&tmr->blocking_mx);
	}
	return (1);
}
