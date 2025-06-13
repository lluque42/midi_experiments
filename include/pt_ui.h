/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:02 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 12:47:33 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_ui.h
 * TODO.
 */

#ifndef PT_UI_H
# define PT_UI_H

# include "piano_trainer.h"

int	pt_ui_init(t_pt *pt);

int	pt_ui_check_if_tty(void);

int	pt_ui_terminate(t_pt *pt);

#endif
