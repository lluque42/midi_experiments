/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_timer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:02 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 02:17:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_timer.h
 * TODO.
 */

#ifndef PT_TIMER_H
# define PT_TIMER_H

# include "piano_trainer.h"

typedef void	(*timer_hndlr_t)(void*);

/**
 * @enum e_tmr_block
 * @brief Base for typedef <b>t_tmr_block</b>.
 * @details This type is used to indicate the blocking type of a timer.
 * @var e_tmr_block::TMR_BLOCK
 * The call to pt_tmr_start() blocks until the timer is done.
 * @var e_tmr_block::TMR_NON_BLOCK
 * The call to pt_tmr_start() doesn't block.
*/
typedef enum e_tmr_block
{
	TMR_NON_BLOCK,
	TMR_BLOCK,
}	t_tmr_block;
/**
 * @typedef t_tmr_block
 * Based on the @link e_tmr_block @endlink enum to indicate
 * the blocking type of a timer.
 */

/**
 * @struct s_tmr
 * @brief Base for typedef <b>t_tmr</b>.
 * @details
 * TODO.
 *
 * @var s_tmr::TODO
 * TODO
 */
typedef struct s_tmr
{
	int				duration;
	int				tick;
	timer_hndlr_t	tick_hndlr;
	timer_hndlr_t	done_hndlr;
	void			*tick_hndlr_arg;
	void			*done_hndlr_arg;
	int				count;
	pthread_t		counter_thread;
	pthread_mutex_t	blocking_mx;
	t_tmr_block		blocks;
	int				disabled;
	pthread_mutex_t disabled_mx;
}	t_tmr;
/**
 * @typedef t_tmr
 * @brief Based on the @link s_tmr @endlink struct.
 */

t_tmr	*pt_tmr_create(int duration, int tick,
		timer_hndlr_t tick_hndlr, void *tick_hndlr_arg,
		timer_hndlr_t done_hndlr, void *done_hndlr_arg);

void	*pt_tmr_counter(void *tmr_arg);

int		pt_tmr_start(t_tmr *tmr, t_tmr_block block);

void	pt_tmr_disable(t_tmr *tmr);

int		pt_timer_destroy(t_tmr *tmr);

#endif
