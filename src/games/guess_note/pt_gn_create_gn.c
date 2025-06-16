/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gn_create_gn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:14:33 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 02:15:00 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt_gn	*pt_gn_create_gn(void)
{
	t_pt_gn	*gn;

	gn = ft_calloc(sizeof(t_pt_gn), 1);
	if (gn == NULL)
		return (perror("Calloc'ing gn"), NULL);
	pthread_mutex_init(&gn->note_mx, NULL);
	gn->ask_note = calloc(sizeof(t_note), 1);
	if (gn->ask_note == NULL)
		return (perror("calloc'ing note"), NULL); // free more
	gn->guess_note = calloc(sizeof(t_note), 1);
	if (gn->guess_note == NULL)
		return (perror("calloc'ing note"), NULL); // free more
	return (gn);
}
