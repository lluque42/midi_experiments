/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_sig_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:59:04 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 23:03:25 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_sig_init(void)
{
	if (signal(SIGINT, &pt_sig_hndlr) == SIG_ERR)
	{
		perror("Couldnt register signal handler for SIGINT");
		return (0);
	}

	if (signal(SIGWINCH, &pt_sig_hndlr) == SIG_ERR)
	{
		perror("Couldnt register signal handler for SIGWINCH");
		return (0);
	}
	return (1);
}
