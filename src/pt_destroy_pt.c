/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_destroy_pt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:55:42 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 13:11:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_destroy_pt(t_pt *pt)
{
	free(pt->midi_dev_file);
	pthread_mutex_destroy(&pt->flags_mx);
	pthread_mutex_destroy(&pt->note_mx);
	free(pt->env_termtype);
	free(pt);
}
