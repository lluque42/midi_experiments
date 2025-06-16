/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_create_pt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:55:42 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:13:12 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt	*pt_create_pt(void)
{
	t_pt	*pt;

	pt = calloc(sizeof(t_pt), 1);
	if (pt == NULL)
		return (perror("creating pt control struct"), NULL);
	pthread_mutex_init(&pt->flags_mx, NULL);
	pthread_mutex_init(&pt->ws_mx, NULL);
	pthread_mutex_init(&pt->screen_mx, NULL);
	pt->midi = pt_midi_create_midi();
	if (pt->midi == NULL)
		return (NULL); // and free lots of shit
	pt->gn = pt_gn_create_gn();
	if (pt->gn == NULL)
		return (NULL); // and free lots of shit
	return (pt);
}
