/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_tmr_disable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:03:14 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 22:06:58 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_tmr_disable(t_tmr *tmr)
{
	pthread_mutex_lock(&tmr->disabled_mx);
	tmr->disabled = 1;
	pthread_mutex_unlock(&tmr->disabled_mx);
}
