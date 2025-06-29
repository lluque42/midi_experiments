/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_tmr_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:03:24 by lluque            #+#    #+#             */
/*   Updated: 2025/06/29 11:20:36 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_tmr_destroy(t_tmr *tmr)
{
	if (tmr == NULL)
		return (1);
	pthread_join(pt->gn->question_tmr->counter_thread, NULL);
	pthread_mutex_destroy(&tmr->blocking_mx);
	pthread_mutex_destroy(&tmr->disabled_mx);
	free(tmr);
	return (1);
}
