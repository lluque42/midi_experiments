/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:21:57 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 01:39:30 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt	*pt;

int	main(int argc, char **argv)
{
	t_pt			*pt;

	if (argc > 1)
		printf("argv[0] = %s\n", argv[0]);
	
	pt = pt_create_pt();
	if (pt == NULL)
		return (EXIT_FAILURE);
	if (!pt_art_init(pt))
		return (pt_destroy_pt(pt), EXIT_FAILURE);
	if (!pt_sig_init())
		return (pt_destroy_pt(pt), EXIT_FAILURE);
	if (!pt_ui_init(pt))
		return (pt_destroy_pt(pt), EXIT_FAILURE);
	if (!pt_midi_try_connect(pt))
		return (pt_destroy_pt(pt), pt_ui_terminate(pt), EXIT_FAILURE);
	if (pthread_create(&pt->midi->listener_thread, NULL, &pt_midi_listener, pt))
		return (pt_destroy_pt(pt), pt_ui_terminate(pt), close(pt->midi->dev_fd),
				perror("creating listener_thread"), EXIT_FAILURE);
/*
	int	i = 60;
	t_note  *note;
	while (i < 73)
	{
		note = pt_mu_create_note_from_midi(i);
		pt_mu_note_print(pt, note);
		pt_art_print_in_columns(pt, pt->min_ws, 2,
				pt->lat_notes, note->pse_diaton,
				pt->alts, note->dia_alteration);
		printf("\n");
		free(note);
		i++;
	}
*/	
	
	
	
	
	sleep(3);
	// May be a menu to select a game
	// and to configure preferences 
	if (!pt_gm_guess_note(pt))
		dprintf(STDERR_FILENO, "Couldn't load game\n");
	pthread_join(pt->midi->listener_thread, NULL);
	close(pt->midi->dev_fd);
	pt_ui_terminate(pt);
	pt_destroy_pt(pt);
	return (EXIT_SUCCESS);
}
