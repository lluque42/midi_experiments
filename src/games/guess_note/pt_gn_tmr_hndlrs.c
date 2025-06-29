/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gn_tmr_hndlrs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:03:26 by lluque            #+#    #+#             */
/*   Updated: 2025/06/26 22:03:59 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_gn_tmr_tick_hndlr(void *pt_arg)
{
	t_pt	*pt;

	pt = (t_pt *)pt_arg;
	pthread_mutex_lock(&pt->flags_mx);
	if (pt->exit_pending)
	{
		pthread_mutex_unlock(&pt->flags_mx);
		pt_tmr_disable(pt->gn->question_tmr);
		return ;
	}
	pthread_mutex_unlock(&pt->flags_mx);
	pt->gn->count--;
	pt_gn_render(pt);
}

void	pt_gn_tmr_done_hndlr(void *pt_arg)
{
	t_pt	*pt;
	pt = (t_pt *)pt_arg;
	pt_gn_render(pt);
}
