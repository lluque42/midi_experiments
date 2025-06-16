/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:06:44 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_midi.h
 * TODO.
 */

#ifndef PT_MIDI_H
# define PT_MIDI_H

# include "piano_trainer.h"

# define BUFFER_SIZE 256

/*
Extract from https://midi.org/summary-of-midi-1-0-messages

Table 1: MIDI 1.0 Specification Message Summary
Status
D7—-D0	
Data Byte(s)
D7—-D0

Channel Voice Messages [nnnn = 0-15 (MIDI Channel Number 1-16)] 

Note Off event.
This message is sent when a note is released (ended).
(kkkkkkk) is the key (note) number. (vvvvvvv) is the velocity.
	1000nnnn	(status byte)
	0kkkkkkk	(data byte 1)
	0vvvvvvv	(data byte 2)
Note On event.
This message is sent when a note is depressed (start).
(kkkkkkk) is the key (note) number. (vvvvvvv) is the velocity.
	1001nnnn	(status byte)
	0kkkkkkk	(data byte 1)
	0vvvvvvv	(data byte 2)
*/

typedef enum e_midi_status_msg_type
{
	MIDI_TONE_OFF = 0b10000000,
	MIDI_TONE_ON = 0b10010000,
}	t_midi_status_msg_type;

typedef enum e_midi_receiver_state
{
	MIDI_ST_IDLE,
	MIDI_ST_STATUS,
	MIDI_ST_DATA,
}	t_midi_receiver_state;

/*
 * This link is (I think, because for the official one you have to pay or it's
 * down) the midi specificiations:
http://midi.teragonaudio.com/tech/midispec.htm
The first data is the note number. There are 128 possible notes on a MIDI
device, numbered 0 to 127 (where Middle C is note number 60).
This indicates which note should be played.

https://studiocode.dev/resources/midi-middle-c/
Middle C is MIDI Note Number 60.

This can be C3 or C4, or even C2 or C5. There is no defined standard or
convention. The MIDI standard only says that the note number 60 is a C,
it does not say of which octave.
*/

/**
 * @struct s_pt_midi
 * @brief Base for typedef <b>t_pt_midi</b>.
 * @details
 * TODO.
 *
 * @var s_pt_midi::midi_dev_file
 * The path to the midi character device file if found.
 *
 * @var s_pt_midi::dev_fd
 * The file descriptor to the midi character device file.
 *
 * @var s_pt_midi::listener_thread
 * The MIDI listener thread.
 */
typedef struct s_pt_midi
{
	char					*dev_file;
	int						dev_fd;
	pthread_t				listener_thread;
}	t_pt_midi;
/**
 * @typedef t_pt_midi
 * @brief Based on the @link s_pt_midi @endlink struct.
 */

t_pt_midi	*pt_midi_create_midi(void);

void		pt_midi_destroy_midi(t_pt_midi *midi);

void		*pt_midi_listener(void *pt_control_struct);

int			pt_midi_try_connect(t_pt *pt);

#endif
