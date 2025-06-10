/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piano_trainer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:20:48 by lluque            #+#    #+#             */
/*   Updated: 2025/06/10 23:16:41 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIANO_TRAINER_H
# define PIANO_TRAINER_H

# include "libft.h"
# include <sys/types.h>	// dir related functions stdlib
# include <dirent.h>	// dir related functions stdlib
# include <stdio.h>		// perror()
# include <errno.h>
# include <dirent.h>	// readdir()
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>		// open() flags, modes
# include <unistd.h>	// read()



// Advanced Linux Sound Architecture, the new aproach
# define ALSA_DEV_FILES_BASE_DIR "/dev/snd/"

// Open Sound System, legacy
# define OSS_DEV_FILES_BASE_DIR "/dev/dsp/"

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
The first data is the note number. There are 128 possible notes on a MIDI device, numbered 0 to 127 (where Middle C is note number 60). This indicates which note should be played.

https://studiocode.dev/resources/midi-middle-c/
Middle C is MIDI Note Number 60.

This can be C3 or C4, or even C2 or C5. There is no defined standard or convention. The MIDI standard only says that the note number 60 is a C, it does not say of which octave.
*/

#endif
