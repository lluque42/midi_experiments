/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/11 23:08:41 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	*pt_midi_listener(void *pt_control_struct);

#endif
