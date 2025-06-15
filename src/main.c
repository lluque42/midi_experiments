/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:21:57 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 18:43:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_pt	*pt;

// From 0 to max
int	pt_get_rand_nbr(int max, unsigned int *seed)
{
	struct timeval	timestamp;
	int				nbr;
	int				unbiased_limit;

	if (*seed == 0)
	{
		if (gettimeofday(&timestamp, NULL) == -1)
			return (perror("asking for time"), -1);
		*seed = timestamp.tv_sec;
		srand(*seed);
	}
	unbiased_limit = RAND_MAX - (RAND_MAX % (max + 1));
	nbr = RAND_MAX;
	while (nbr >= unbiased_limit)
		nbr = rand();
	nbr = nbr % (max + 1);
	return (nbr);
}

void	tmr_tick_hndlr(void *pt_arg)
{
	t_pt	*pt;

	pt = (t_pt *)pt_arg;
	pthread_mutex_lock(&pt->screen_mx);
	printf ("tick! %p\n", pt);
	pthread_mutex_unlock(&pt->screen_mx);
}

void	tmr_done_hndlr(void *pt_arg)
{
	t_pt	*pt;

	pt = (t_pt *)pt_arg;
	pthread_mutex_lock(&pt->screen_mx);
	printf ("done! %p\n", pt);
	pthread_mutex_unlock(&pt->screen_mx);
}

int	main(int argc, char **argv)
{
	t_pt			*pt;
	int				rand_note;
	int				rand_alteration;
	int				rand_note_naming;
	t_pt_ascii_art	*current_note_naming;

	if (argc > 1)
		printf("argv[0] = %s\n", argv[0]);
	
	pt = pt_create_pt();
	if (pt == NULL)
		return (EXIT_FAILURE);


	if (!pt_sig_init())
		return (pt_destroy_pt(pt), EXIT_FAILURE);

	if (!pt_ui_init(pt))
		return (pt_destroy_pt(pt), EXIT_FAILURE);
	

//	struct winsize logo_size;
//
//	logo_size = pt_ui_get_art_size("data/logo");
//	printf("rows = %d cols = %d\n", logo_size.ws_row, logo_size.ws_col);


	pt->logo = pt_art_load_art(PT_LOGO_PATH, 1, 1);	
	pt->alts = pt_art_load_art(PT_ALTERATIONS_PATH, 4, 1);	
	
	pt->ang_notes = pt_art_load_art(PT_ANG_NOTES_PATH, 7, 1);
	pt->lat_notes = pt_art_load_art(PT_LAT_NOTES_PATH, 7, 1);
	pt->numbers = pt_art_load_art(PT_NUMBERS_PATH, 10, 1);

	pt_art_print_in_columns(pt->logo->size, 1,
							pt->numbers, 1);
	pt_art_print_in_columns(pt->logo->size, 1,
							pt->alts, 1);
	pt_art_print_in_columns(pt->logo->size, 1,
							pt->lat_notes, 1);
	pt_art_print_in_columns(pt->logo->size, 1,
							pt->ang_notes, 1);

	pt_art_print_in_columns(pt->logo->size, 4,
							pt->numbers, 1,
							pt->alts, 2,
							pt->lat_notes, 3,
							pt->ang_notes, 4);





//	pt_art_print_in_columns(pt->logo->size, 1,
//							pt->numbers, 1);
	


//	pt_art_print_in_columns(pt->logo->size, 4,
//							pt->lat_notes, 5,
//							pt->alts, 1,
//							pt->numbers, 4,
//							pt->numbers, 6);

	// May be a menu
	if (!pt_midi_try_connect(pt))
		return (pt_destroy_pt(pt), pt_ui_terminate(pt), EXIT_FAILURE);

	if (pthread_create(&pt->listener_thread, NULL, &pt_midi_listener, pt))
		return (pt_destroy_pt(pt), pt_ui_terminate(pt), close(pt->dev_fd),
				perror("creating listener_thread"), EXIT_FAILURE);
	sleep(2);

	while (1)
	{
		pthread_mutex_lock(&pt->flags_mx);
		if (pt->exit_pending)
		{
			pthread_mutex_unlock(&pt->flags_mx);
			break ;
		}
		pthread_mutex_unlock(&pt->flags_mx);
		rand_note = pt_get_rand_nbr(6, &pt->seed);
		rand_alteration = pt_get_rand_nbr(3, &pt->seed);
		rand_note_naming = pt_get_rand_nbr(0, &pt->seed);
		if (rand_note_naming)
			current_note_naming = pt->ang_notes;
		else
			current_note_naming = pt->lat_notes;
	
	
		//clear the screen before each note
		printf("%s", tgetstr("cl", NULL));
		//printf("Try this note: %s\n", latin_notes_sharp[rand_note]);
		
		pt_art_print_in_columns(pt->logo->size, 2,
								current_note_naming, rand_note,
								pt->alts, rand_alteration);



		pt->question_tmr = pt_tmr_create(5000, 1000,
									tmr_tick_hndlr, (void *)pt,
									tmr_done_hndlr, (void *)pt);
		if (pt->question_tmr == NULL)
			return (EXIT_FAILURE);//////////
		pt_tmr_start(pt->question_tmr, TMR_BLOCK);




		pthread_mutex_lock(&pt->note_mx);
		if (pt->last_note == rand_note)
		{
			pthread_mutex_lock(&pt->screen_mx);
			printf ("Well done!!!!\n");
			pthread_mutex_unlock(&pt->screen_mx);
		}
		else
		{
			pthread_mutex_lock(&pt->screen_mx);
			printf ("Wrong!\n");
			pthread_mutex_unlock(&pt->screen_mx);
		}
		pthread_mutex_lock(&pt->screen_mx);
//		printf("You pressed: %s%d\n", latin_notes_sharp[pt->last_note],
//				pt->last_octave);
		pthread_mutex_unlock(&pt->screen_mx);
		pt->last_note = 0;
		pthread_mutex_unlock(&pt->note_mx);
	}

	pthread_join(pt->listener_thread, NULL);
	close(pt->dev_fd);
	pt_ui_terminate(pt);
	pt_destroy_pt(pt);
	return (EXIT_SUCCESS);
}

//2212221 = 12 (major scale)


