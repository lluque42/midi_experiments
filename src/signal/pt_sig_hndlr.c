/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_sig_hndlr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:04:41 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 23:05:43 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_sig_hndlr(int signal)
{
	printf ("...\n");
	if (signal == SIGINT)
	{
		printf ("\nPlease don't go\n");
		pthread_mutex_lock(&pt->flags_mx);
		pt->exit_pending = 1;
		pt_tmr_disable(pt->question_tmr);
		pthread_mutex_unlock(&pt->flags_mx);
	}
	else if (signal == SIGWINCH)
	{
		pthread_mutex_lock(&pt->ws_mx);
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &pt->ws) == -1)
		{
			pthread_mutex_unlock(&pt->ws_mx);
			perror("ioctl for terminal size");
			pthread_mutex_lock(&pt->flags_mx);
			pt->exit_pending = 1;
			pthread_mutex_unlock(&pt->flags_mx);
		}
		pthread_mutex_unlock(&pt->ws_mx);
	}
}
