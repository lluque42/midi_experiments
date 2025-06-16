/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:07:13 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 19:07:33 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int pt_midi_init(t_pt *pt)
{
	if (!pt_midi_try_connect(pt))
		return (0);
	pt_midi_register_handler(pt->midi, MIDI_TONE_ON,
			pt_midi_tone_on_off_default);
	pt_midi_register_handler(pt->midi, MIDI_TONE_OFF,
			pt_midi_tone_on_off_default);
	if (pthread_create(&pt->midi->listener_thread, NULL, &pt_midi_listener, pt))
		return (close(pt->midi->dev_fd), 
				perror("creating listener_thread"), 0);
	return (1);
}
