/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_mu_create_note_from_chrom.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:37:38 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 21:39:45 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

t_note	*pt_mu_create_note_from_chrom(int chrom)
{
	t_note  *note;
	int		i;

	note = calloc(sizeof(t_note), 1);
	if (note == NULL)
		return (perror("Calloc'ing note"), NULL);
	note->midi = -1;
	note->chrom = chrom;
	note->octave = -1;
	note->pse_diaton = 0;
	note->dia_alteration = 0;
	i = 0;
	while (MAJ_SCALE[i] != '\0')
	{
		if (note->pse_diaton == note->chrom)
			break ;
		if (MAJ_SCALE[i] - '0' > 1)
		{
			if (note->pse_diaton + 1 == note->chrom)
			{
				note->dia_alteration = 1;
				break ;
			}
			note->pse_diaton += MAJ_SCALE[i] - '0';
			i++;
			if (note->pse_diaton == note->chrom)
				break ;
		}
		else
		{
			note->pse_diaton += MAJ_SCALE[i] - '0';
			i++;
			if (note->pse_diaton == note->chrom)
				break ;
			//if (note->pse_diaton > note->chrom)
				// Some problem with the scale
		}
	}
	note->pse_diaton = i;
	return (note);
}
