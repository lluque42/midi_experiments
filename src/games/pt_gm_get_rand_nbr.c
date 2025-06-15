/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_gm_get_rand_nbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:14:09 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 20:14:58 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

// From 0 to max
int	pt_gm_get_rand_nbr(int max, unsigned int *seed)
{
	struct timeval	timestamp;
	int				nbr;
	int				unbiased_limit;

	if (*seed == 0)
	{
		if (gettimeofday(&timestamp, NULL) == -1)
			return (perror("asking for time"), -1);
		*seed = timestamp.tv_sec;
		srand(*seed);
	}
	unbiased_limit = RAND_MAX - (RAND_MAX % (max + 1));
	nbr = RAND_MAX;
	while (nbr >= unbiased_limit)
		nbr = rand();
	nbr = nbr % (max + 1);
	return (nbr);
}
