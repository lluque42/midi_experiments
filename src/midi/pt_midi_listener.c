/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_listener.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:30:26 by lluque            #+#    #+#             */
/*   Updated: 2025/06/11 22:56:13 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	*pt_midi_listener(void *pt_control_struct)
{

	pt = (t_pt*)pt_control_struct;

	int bc;
	int	i;
	int data_bytes_expected;
	int	data_bytes_count;
	unsigned char	input_buffer[BUFFER_SIZE];


	t_midi_receiver_state	state;

	state = MIDI_ST_IDLE;

	t_midi_status_msg_type	midi_status;
//	int						midi_channel;
//	int						midi_key;
//	int						midi_vel;
	while (1)
	{
		pthread_mutex_lock(&pt->flags_mx);
		if (pt->exit_pending)
			return (pthread_mutex_unlock(&pt->flags_mx), NULL);
		pthread_mutex_unlock(&pt->flags_mx);
		bc = read(pt->dev_fd, &input_buffer, BUFFER_SIZE);
		if (bc == -1)
		{
			if (errno != EWOULDBLOCK || errno != EAGAIN)
				return (close(pt->dev_fd), perror("reading"), NULL);
		}
		if (bc == 0)
			break ;
		i = -1;
		while (++i < bc)
		{
//			printf("bc = %d i = %d\n", bc, i);
			if (state == MIDI_ST_IDLE)
			{
				if ((input_buffer[i] & 128) == 0)
					return (close(pt->dev_fd), printf("unexpected data byte when expecting a status byte"), NULL);
				midi_status = input_buffer[i] & 0xf0;
//				midi_channel = input_buffer[i] & 0xf;
				if (midi_status == MIDI_TONE_OFF)
				{
//					printf("tone off detected on channel %d\n", midi_channel);
					state = MIDI_ST_STATUS;
					data_bytes_expected = 2;
					data_bytes_count = 0;
					continue ;
				}
				else if (midi_status == MIDI_TONE_ON)
				{
//					printf("tone on detected on channel %d\n", midi_channel);
					state = MIDI_ST_STATUS;
					data_bytes_expected = 2;
					data_bytes_count = 0;
					continue ;
				}
			}
			if (state == MIDI_ST_STATUS && data_bytes_count <= data_bytes_expected)
			{
				if ((input_buffer[i] & 128) != 0)
					return (close(pt->dev_fd), printf("unexpected status byte when expecting a data byte"), NULL);
				data_bytes_count++;
//				printf("Data byte %d value = %d\n", data_bytes_count, input_buffer[i]);
				if (midi_status == MIDI_TONE_OFF || midi_status == MIDI_TONE_ON)
				{
					if (data_bytes_count == 1)
					{
//						midi_key = input_buffer[i];
						pthread_mutex_lock(&pt->note_mx);
						pt->last_note = input_buffer[i] % 12;
						// 60 is middle C, so it can vary. For my 88 keys
						// keyboard, the middle C is in the 4th octave,
						// so the key 60 is C4 (do4), this is why I substract 1.
						pt->last_octave = input_buffer[i] / 12 - 1;
						pthread_mutex_unlock(&pt->note_mx);

					}
					else if (data_bytes_count == 2)
					{
//						midi_vel = input_buffer[i];
//						printf("The velocity is %d\n", midi_vel);
					}
				}
				if (data_bytes_count == data_bytes_expected)
				{
					state = MIDI_ST_IDLE;
				}
				continue ;
			}
		}
	}

	return (NULL);
}

