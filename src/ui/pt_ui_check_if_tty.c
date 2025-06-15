/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui_check_if_tty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:59:58 by lluque            #+#    #+#             */
/*   Updated: 2025/06/14 11:30:10 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_ui_check_if_tty(void)
{
	if (!isatty(STDERR_FILENO) || !isatty(STDOUT_FILENO)
			|| !isatty(STDIN_FILENO))
		return (0);
	return (1);
}
