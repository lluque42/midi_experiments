/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:21:57 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 21:02:30 by lluque           ###   ########.fr       */
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
	if (!pt_midi_init(pt))
		return (pt_ui_terminate(pt), pt_destroy_pt(pt), EXIT_FAILURE);

	// To try the default midi handlers
//	while(1)
//	{
//		pthread_mutex_lock(&pt->flags_mx);
//		if (pt->exit_pending)
//		{
//			pthread_mutex_unlock(&pt->flags_mx);
//			break;
//		}
//		pthread_mutex_unlock(&pt->flags_mx);
//		sleep(1);
//	}
	
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
