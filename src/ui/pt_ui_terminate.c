/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui_terminate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:59:58 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 13:52:59 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_ui_terminate(t_pt *pt)
{
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &pt->termios_orig) != 0)
		return (0);
	// This call makes termcap to free 
	//status = tgetent (NULL, pt->env_termtype);	// won't free shit
	//printf("%s", tgetstr("cl", NULL));
	return (1);
}
