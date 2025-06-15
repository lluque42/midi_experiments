/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_tmr_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:20:51 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 22:11:49 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	*pt_tmr_counter(void *tmr_arg)
{
	t_tmr	*tmr;
	int		count;
	int		max;

	tmr = (t_tmr *)tmr_arg;
	pthread_mutex_lock(&tmr->blocking_mx);
	count = 0;
	max = ceil(((float)tmr->duration) / ((float)tmr->tick));
	while (count < max)
	{
		usleep(1000 * tmr->tick);
		pthread_mutex_lock(&tmr->disabled_mx);
		if (!tmr->disabled)
		{
			tmr->tick_hndlr(tmr->tick_hndlr_arg);
			pthread_mutex_unlock(&tmr->disabled_mx);
		}
		else
		{
			pthread_mutex_unlock(&tmr->disabled_mx);
			break ;
		}
		count++;
	}
	pthread_mutex_lock(&tmr->disabled_mx);
	if (!tmr->disabled)
	{
		pthread_mutex_unlock(&tmr->disabled_mx);
		tmr->done_hndlr(tmr->done_hndlr_arg);
	}
	else
		pthread_mutex_unlock(&tmr->disabled_mx);

	if (tmr->blocks)
		pthread_mutex_unlock(&tmr->blocking_mx);
	return (NULL);
}
