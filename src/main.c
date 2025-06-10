/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:21:57 by lluque            #+#    #+#             */
/*   Updated: 2025/06/10 23:43:54 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "piano_trainer.h"

int	main(int argc, char **argv)
{
	char			*midi_dev_file;
	unsigned char	input_buffer[BUFFER_SIZE];
	char			*latin_notes_sharp[] = {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};

	midi_dev_file = NULL;

	if (argc > 1)
		printf("argv[0] = %s\n", argv[0]);
	ft_printf("hello piano learner\n");


	DIR	*dev_snd;

	dev_snd = opendir(ALSA_DEV_FILES_BASE_DIR);
	if (dev_snd == NULL)
	{
		printf("No ALSA device file directory found (%s), trying for OSS...\n",
				ALSA_DEV_FILES_BASE_DIR);
		dev_snd = opendir(OSS_DEV_FILES_BASE_DIR);
		if (dev_snd == NULL)
			return (printf("No OSS device file directory found either (%s), terminating the program\n",
						OSS_DEV_FILES_BASE_DIR), EXIT_FAILURE);
	}
	struct dirent	*current_dir_entry;
	current_dir_entry = readdir(dev_snd);
	while (current_dir_entry != NULL)
	{
		printf("item '%s' is of type '%d'\n", current_dir_entry->d_name,
				current_dir_entry->d_type);
		if (ft_strncmp(current_dir_entry->d_name,
					"midi", 4) == 0)
		{
			if (current_dir_entry->d_type == DT_UNKNOWN)
			{
				//try with lstat
			}
			else if (current_dir_entry->d_type == DT_CHR)
			{
				printf("This is probably the midi device file: %s%s\n", ALSA_DEV_FILES_BASE_DIR, current_dir_entry->d_name);
				midi_dev_file = calloc(sizeof (char), strlen(ALSA_DEV_FILES_BASE_DIR) + strlen(current_dir_entry->d_name) + 1);
				if (midi_dev_file == NULL)
					return (perror(""), closedir(dev_snd), EXIT_FAILURE);
				memcpy(midi_dev_file, ALSA_DEV_FILES_BASE_DIR, strlen(ALSA_DEV_FILES_BASE_DIR));
				memcpy(midi_dev_file + strlen(ALSA_DEV_FILES_BASE_DIR), current_dir_entry->d_name, strlen(current_dir_entry->d_name));

			}
		}
		current_dir_entry = readdir(dev_snd);
	//	if (current_dir_entry->d_type == DT_UNKNOWN)
	}
	closedir(dev_snd);
	if (midi_dev_file == NULL)
		return (printf("No midi device file was found, make sure your keyboard is connected and tie to a driver\n"), EXIT_FAILURE);
	printf("So let's work with '%s'\n", midi_dev_file);


	int	fd;
	int bc;
	int	i;
	int data_bytes_expected;
	int	data_bytes_count;

/*
 * O_ASYNC
              Enable  signal-driven  I/O: generate a signal (SIGIO by default,
              but this can be changed via fcntl(2)) when input or  output  be‐
              comes  possible on this file descriptor.  This feature is avail‐
              able only for terminals, pseudoterminals,  sockets,  and  (since
              Linux  2.6)  pipes and FIFOs.  See fcntl(2) for further details.
              See also BUGS, below.
			  */
	fd = open(midi_dev_file, O_RDONLY);
	if (fd == -1)
		return (perror("opening device file"), EXIT_FAILURE);

	t_midi_receiver_state	state;

	state = MIDI_ST_IDLE;

	t_midi_status_msg_type	midi_status;
	int						midi_channel;
	int						midi_key;
	int						midi_vel;
	while (1)
	{

		bc = read(fd, &input_buffer, BUFFER_SIZE);
		if (bc == -1)
			return (close(fd), perror("reading"), EXIT_FAILURE);
		if (bc == 0)
			break ;
		i = -1;
		while (++i < bc)
		{
			printf("bc = %d i = %d\n", bc, i);
			if (state == MIDI_ST_IDLE)
			{
				if ((input_buffer[i] & 128) == 0)
					return (close(fd), printf("unexpected data byte when expecting a status byte"), EXIT_FAILURE);
				midi_status = input_buffer[i] & 0xf0;
				midi_channel = input_buffer[i] & 0xf;
				if (midi_status == MIDI_TONE_OFF)
				{
					printf("tone off detected on channel %d\n", midi_channel);
					state = MIDI_ST_STATUS;
					data_bytes_expected = 2;
					data_bytes_count = 0;
					continue ;
				}
				else if (midi_status == MIDI_TONE_ON)
				{
					printf("tone on detected on channel %d\n", midi_channel);
					state = MIDI_ST_STATUS;
					data_bytes_expected = 2;
					data_bytes_count = 0;
					continue ;
				}
			}
			if (state == MIDI_ST_STATUS && data_bytes_count <= data_bytes_expected)
			{
				if ((input_buffer[i] & 128) != 0)
					return (close(fd), printf("unexpected status byte when expecting a data byte"), EXIT_FAILURE);
				data_bytes_count++;
				printf("Data byte %d value = %d\n", data_bytes_count, input_buffer[i]);
				if (midi_status == MIDI_TONE_OFF || midi_status == MIDI_TONE_ON)
				{
					if (data_bytes_count == 1)
					{
						midi_key = input_buffer[i];
						printf("The note is %s%d\n", latin_notes_sharp[midi_key % 12], midi_key/12 - 1); // 60 is middle C, so it can vary. For my 88 keys keyboard, the middle C is in the 4th octave, so the key 60 is C4 (do4), this is why I substract 1.
					}
					else if (data_bytes_count == 2)
					{
						midi_vel = input_buffer[i];
						printf("The velocity is %d\n", midi_vel);
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




	return (close(fd), EXIT_SUCCESS);
}
