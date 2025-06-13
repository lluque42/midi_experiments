/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:21:57 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 12:54:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt	*pt;
char	*latin_notes_sharp[] = {"do", "do#", "re", "re#", "mi", "fa",
								"fa#", "sol", "sol#", "la", "la#", "si"};
char	*latin_notes_flat[] = {"do", "reb", "re", "mib", "mi", "fa",
								"solb", "sol", "lab", "la", "sib", "si"};
char	*angl_notes_sharp[] = {"C", "C#", "D", "D#", "E", "F",
								"F#", "G", "G#", "A", "A#", "B"};
char	*angl_notes_flat[] = {"C", "Db", "D", "Eb", "E", "F",
								"Gb", "G", "Ab", "A", "Bb", "B"};

void	pt_sig_hndlr(int signal)
{
	printf ("...\n");
	if (signal == SIGINT)
	{
		printf ("\nPlease don't go\n");
		pthread_mutex_lock(&pt->flags_mx);
		pt->exit_pending = 1;
		pthread_mutex_unlock(&pt->flags_mx);
	}
}

int	pt_get_rand_note(t_pt *pt)
{
	struct timeval	timestamp;
	int				note;
	int				unbiased_limit;

	if (pt->seed == 0)
	{
		if (gettimeofday(&timestamp, NULL) == -1)
			return (perror("asking for time"), -1);
		pt->seed = timestamp.tv_sec;
		srand(pt->seed);
	}
	unbiased_limit = RAND_MAX - (RAND_MAX % 12);
	note = RAND_MAX;
	while (note >= unbiased_limit)
		note = rand();
	note = note % 12;
	return (note);
}

int	main(int argc, char **argv)
{
	t_pt	*pt;
	int		rand_note;

	if (argc > 1)
		printf("argv[0] = %s\n", argv[0]);
	
	pt = pt_create_pt();
	if (pt == NULL)
		return (EXIT_FAILURE);

	if (signal(SIGINT, &pt_sig_hndlr) == SIG_ERR)
	{
		perror("Couldnt register signal handler for SIGINT");
		return (EXIT_FAILURE);
	}

	if (!pt_ui_init(pt))
		return (pt_destroy_pt(pt), EXIT_FAILURE);

	pt->midi_dev_file = pt_files_get_midi_dev_file();
	if (pt->midi_dev_file == NULL)
	{
		dprintf(STDERR_FILENO, "No midi device file was found, ");
		dprintf(STDERR_FILENO, "make sure your keyboard is connected ");
		dprintf(STDERR_FILENO, "and tied to a driver\n");
		return (pt_destroy_pt(pt), pt_ui_terminate(pt), EXIT_FAILURE);
	}
	pt->dev_fd = open(pt->midi_dev_file, O_RDONLY | O_NONBLOCK);
	if (pt->dev_fd == -1)
		return (pt_destroy_pt(pt), pt_ui_terminate(pt),
				perror("opening device file"), EXIT_FAILURE);
	if (pthread_create(&pt->listener_thread, NULL, &pt_midi_listener, pt))
		return (pt_destroy_pt(pt), pt_ui_terminate(pt), close(pt->dev_fd),
				perror("creating listener_thread"), EXIT_FAILURE);

	while (1)
	{
		pthread_mutex_lock(&pt->flags_mx);
		if (pt->exit_pending)
		{
			pthread_mutex_unlock(&pt->flags_mx);
			break ;
		}
		pthread_mutex_unlock(&pt->flags_mx);
		rand_note = pt_get_rand_note(pt);
		printf("Try this note: %s\n", latin_notes_sharp[rand_note]);
		sleep(5);
		pthread_mutex_lock(&pt->note_mx);
		if (pt->last_note == rand_note)
			printf ("Well done!!!!\n");
		else
			printf ("Wrong!\n");
		printf("You pressed: %s%d\n", latin_notes_sharp[pt->last_note],
				pt->last_octave);
		pt->last_note = 0;
		pthread_mutex_unlock(&pt->note_mx);
	}

	pthread_join(pt->listener_thread, NULL);
	close(pt->dev_fd);
	pt_ui_terminate(pt);
	pt_destroy_pt(pt);
	return (EXIT_SUCCESS);
}
