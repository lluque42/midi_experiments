/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui_clear_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:59:58 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 19:43:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_ui_clear_screen(t_pt *pt)
{
	char *clearer_str;

	pthread_mutex_lock(&pt->screen_mx);
   	clearer_str = tgetstr("cl", NULL);
	write(STDIN_FILENO, clearer_str, strlen(clearer_str)); 
	pthread_mutex_unlock(&pt->screen_mx);
}
