/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi_listener.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:30:26 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 21:00:11 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

static int	pt_midi_discarding_case(t_pt *pt, int *i)
{
	if ((pt->midi->input_buffer[*i] & 128) == 0)
	{
		*i = *i + 1;
		return (1);
	}
	if ((pt->midi->input_buffer[*i] & 128) != 0)
	{
		pt->midi->state = MIDI_ST_IDLE;
		return (1);
	}
	return (0);
}

static int	pt_midi_iddle_case(t_pt *pt, int *i)
{
	if ((pt->midi->input_buffer[*i] & 128) == 0)
		return (close(pt->midi->dev_fd),
			dprintf(STDERR_FILENO, "unexpected data byte when expecting a status byte"), 0);
	pt->midi->tone_msg.status = pt->midi->input_buffer[*i] & 0xf0;
	pt->midi->tone_msg.channel = pt->midi->input_buffer[*i] & 0x0f;
	if (pt->midi->tone_msg.status == MIDI_TONE_OFF)
	{
		pt->midi->state = MIDI_ST_DATA;
		pt->midi->data_bytes_expected = 2;
		pt->midi->data_bytes_count = 0;
		*i = *i + 1;
		return (1);
	}
	else if (pt->midi->tone_msg.status == MIDI_TONE_ON)
	{
		pt->midi->state = MIDI_ST_DATA;
		pt->midi->data_bytes_expected = 2;
		pt->midi->data_bytes_count = 0;
		*i = *i + 1;
		return (1);
	}
	pt->midi->state = MIDI_ST_DISCARDING;
	*i = *i + 1;
	return (1);
}

static int	pt_midi_data_case(t_pt *pt, int *i)
{
	//&& pt->midi->data_bytes_count <= pt->midi->data_bytes_expected)
	if ((pt->midi->input_buffer[*i] & 128) != 0)
		return (close(pt->midi->dev_fd),
				dprintf(STDERR_FILENO,
				"unexpected status byte when expecting data byte"),
				0);
	pt->midi->data_bytes_count++;
	if (pt->midi->tone_msg.status == MIDI_TONE_OFF)
	{
		if (pt->midi->data_bytes_count == 1)
			pt->midi->tone_msg.key = pt->midi->input_buffer[*i];
		else if (pt->midi->data_bytes_count == 2)
		{
			pt->midi->tone_msg.vel = pt->midi->input_buffer[*i];
			pt->midi->on_tone_off((void *)pt, (void *)&pt->midi->tone_msg);
			pt->midi->state = MIDI_ST_IDLE;
		}
	}
	else if (pt->midi->tone_msg.status == MIDI_TONE_ON)
	{
		if (pt->midi->data_bytes_count == 1)
			pt->midi->tone_msg.key = pt->midi->input_buffer[*i];
		else if (pt->midi->data_bytes_count == 2)
		{
			pt->midi->tone_msg.vel = pt->midi->input_buffer[*i];
			pt->midi->on_tone_on((void *)pt, (void *)&pt->midi->tone_msg);
			pt->midi->state = MIDI_ST_IDLE;
		}
	}
	*i = *i + 1;
	return (1);
}

void	*pt_midi_listener(void *pt_control_struct)
{
	int bc;
	int	i;
	int	loop_action;

	pt = (t_pt*)pt_control_struct;
	pt->midi->state = MIDI_ST_IDLE;
	while (1)
	{
		pthread_mutex_lock(&pt->flags_mx);
		if (pt->exit_pending)
			return (pthread_mutex_unlock(&pt->flags_mx), NULL);
		pthread_mutex_unlock(&pt->flags_mx);
		bc = read(pt->midi->dev_fd, &pt->midi->input_buffer, BUFFER_SIZE);
		if (bc == -1)
		{
			if (errno != EWOULDBLOCK || errno != EAGAIN)
				return (close(pt->midi->dev_fd), perror("reading"), NULL);
		}
		if (bc == 0)
			break ;
		i = 0;
		while (i < bc)
		{
			if (pt->midi->state == MIDI_ST_IDLE)
			{
				loop_action = pt_midi_iddle_case(pt, &i);
				if (loop_action == 1)
					continue ;
				else if (loop_action == 0)
					return (NULL); // hmmmm there's no actual error reporting/management
			}
			if (pt->midi->state == MIDI_ST_DISCARDING)
			{
				loop_action = pt_midi_discarding_case(pt, &i);
				if (loop_action == 1)
					continue ;
			}
			if (pt->midi->state == MIDI_ST_DATA)
			{
				loop_action = pt_midi_data_case(pt, &i);
				if (loop_action == 1)
					continue ;
				else if (loop_action == 0)
					return (NULL); // hmmmm there's no actual error reporting/management
			}
		}
	}
	return (NULL);
}
