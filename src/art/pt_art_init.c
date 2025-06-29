/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_art_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:07:28 by lluque            #+#    #+#             */
/*   Updated: 2025/06/26 22:01:14 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_art_init(t_pt *pt)
{
	pt->logo = pt_art_load_art(PT_LOGO_PATH, 1, 1);	
	pt->alts = pt_art_load_art(PT_ALTERATIONS_PATH, 4, 1);	
	pt->ang_notes = pt_art_load_art(PT_ANG_NOTES_PATH, 7, 1);
	pt->lat_notes = pt_art_load_art(PT_LAT_NOTES_PATH, 7, 1);
	pt->numbers = pt_art_load_art(PT_NUMBERS_PATH, 10, 1);
	pt->q_mark = pt_art_load_art(PT_QMARK_PATH, 1, 1);
	pt->blank = pt_art_load_art(PT_BLANK_PATH, 1, 1);
	if (!pt->logo || !pt->alts || !pt->ang_notes
		|| !pt->lat_notes || !pt->numbers || !pt->q_mark || !pt->blank)
		return (0);
	pt->min_ws = pt->logo->size;
	return (1);
}
