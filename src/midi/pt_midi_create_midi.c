/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_create_midi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:10 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:04:23 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt_midi	*pt_midi_create_midi(void)
{
	t_pt_midi	*midi;

	midi = calloc(sizeof(t_pt_midi), 1);
	if (midi == NULL)
		perror("calloc'ing midi");
	return (midi);
}
