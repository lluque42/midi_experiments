/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_games.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:02 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 20:53:23 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_games.h
 * TODO.
 */

#ifndef PT_GAMES_H
# define PT_GAMES_H

# include "piano_trainer.h"
# include "pt_guess_note.h"

int	pt_gm_get_rand_nbr(int max, unsigned int *seed);

int	pt_gm_guess_note(t_pt *pt);

#endif
