/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_midi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 20:15:28 by lluque           ###   ########.fr       */
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

/**
 * @enum e_midi_status_msg_type
 * @brief Base for typedef <b>t_midi_status_msg_type</b>
 * @details
 * Definition of the masks for the status byte (first byte of a midi message)
 * to evaluate type of midi message received.
 * Status byte (for voice aka channel message, that carry channel number):
 * 0 b 1ttt cccc
 * 	t = Type bits
 * 	c = Channel bits
 * @var MIDI_TONE_OFF
 * The message type for tone off (e.g. key release).
 * @var MIDI_TONE_ON
 * The message type for tone on (e.g. key press).
 */
typedef enum e_midi_status_msg_type
{
	// Voice aka channel messages
	MIDI_TONE_OFF =		0b10000000,	// 2 data bytes
	MIDI_TONE_ON =		0b10010000,	// 2 data bytes
	MIDI_AFTERTOUCH = 	0b10100000,	// 2 data bytes
	MIDI_CTRL_CHANGE = 	0b10110000,	// 2 data bytes
	MIDI_PROG_CHANGE = 	0b11000000,	// 1 data bytes
	MIDI_CHAN_PRESS = 	0b11010000,	// 1 data bytes
	MIDI_PITCH_WHEEL =	0b11100000,	// 2 data bytes
	//??? =	0b11110000,	// ??? data bytes
	//These status bytes are further divided into two categories.
	//Status bytes of 0xF0 to 0xF7 are called System Common messages.
	//Status bytes of 0xF8 to 0xFF are called System Realtime messages.
}	t_midi_status_msg_type;
/**
 * @typedef t_midi_status_msg_type
 * @brief Based on the @link e_midi_status_msg_type @endlink enum.
 */

/**
 * @enum e_midi_receiver_state
 * @brief Base for typedef <b>t_midi_receiver_state</b>
 * @details
 * The state of the midi listener.
 * @var MIDI_ST_IDLE
 * Expecting a status byte that indicates the midi message type and
 * hoy many data bytes will follow.
 * @var MIDI_ST_DATA
 * Expecting a known amount of data bytes which are being processed into
 * useful information.
 * @var MIDI_ST_DISCARDING
 * After a status byte for a non-supported feature was received, every
 * data bytes are discarded until a new status byte is detected (which
 * changes the state to MIDI_ST_DATA if supported or again to discard).
 */
typedef enum e_midi_receiver_state
{
	MIDI_ST_IDLE,
	MIDI_ST_DATA,
	MIDI_ST_DISCARDING,
}	t_midi_receiver_state;
/**
 * @typedef t_midi_receiver_state
 * @brief Based on the @link e_midi_receiver_state @endlink enum.
 */

// First argument is program-related. Second argument is for the midi data.
typedef void	(*midi_hndlr_t)(void*, void*);

/**
 * @struct s_pt_midi_tone_msg
 * @brief Base for typedef <b>t_pt_midi_tone_msg</b>.
 * @details
 * This type holds every information for a midi message MIDI_TONE_OFF
 * or MIDI_TONE_ON.
 *
 * @var s_pt_midi_tone_msg::status
 * Either ON (when key is pressed) or OFF (when key is released).
 *
 * @var s_pt_midi_tone_msg::channel
 * The ID of the midi device sending the message (0-15).
 *
 * @var s_pt_midi_tone_msg::key
 * The key number. Remember that the only thing assured is that a value
 * of 60 corresponds to the instrument's middle C. Thus, it varies from
 * instrument to instrument.
 *
 * @var s_pt_midi_tone_msg::vel
 * The velocity of the key press.
 */
typedef struct s_pt_midi_tone_msg
{
	t_midi_status_msg_type	status;
	int						channel;
	int						key;
	int						vel;
}	t_pt_midi_tone_msg;
/**
 * @typedef t_pt_midi_tone_msg
 * @brief Based on the @link s_pt_midi_tone_msg @endlink struct.
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
 *
 * @var s_pt_midi::on_tone_on
 * A handler to be called when a midi tone on message has been received.
 *
 * @var s_pt_midi::on_tone_off
 * A handler to be called when a midi tone on message has been received.
 */
typedef struct s_pt_midi
{

	char					*dev_file;
	int						dev_fd;
	t_midi_receiver_state	state;
	pthread_t				listener_thread;
	midi_hndlr_t			on_tone_on;
	void					*on_tone_on_arg;
	midi_hndlr_t			on_tone_off;
	void					*on_tone_off_arg;
	int 					data_bytes_expected;
	int						data_bytes_count;
	t_pt_midi_tone_msg		tone_msg;
	unsigned char			input_buffer[BUFFER_SIZE];
}	t_pt_midi;
/**
 * @typedef t_pt_midi
 * @brief Based on the @link s_pt_midi @endlink struct.
 */

t_pt_midi	*pt_midi_create_midi(void);

void		pt_midi_destroy_midi(t_pt_midi *midi);

void		*pt_midi_listener(void *pt_control_struct);

int			pt_midi_try_connect(t_pt *pt);

void		pt_midi_tone_on_off_default(void *pt, void *midi_data);

int			pt_midi_init(t_pt *pt);

void		pt_midi_register_handler(t_pt_midi *midi,
										t_midi_status_msg_type msg_type,
										midi_hndlr_t hndlr);
//										void *pt_arg, void *midi_data);
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

#endif
