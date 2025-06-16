/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_art_print_in_columns.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:11:38 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 23:05:41 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_art_print_in_columns(t_pt *pt, struct winsize max_size, int cols, ...)
{
//	printf("[pt_art_print_in_columns] Entering\n");
	t_pt_ascii_art	**art;
	int				*art_vindex;
	va_list			args;
	int				i;
	int				acc_cols;
	int				max_rows;

	art = calloc(sizeof (t_pt_ascii_art*) * cols, 1);
	if (art == NULL)
		return (perror("malloc'ing art columns"), 0);
	art_vindex = malloc(sizeof (int) * max_size.ws_row);
	if (art_vindex == NULL)
		return (perror("malloc'ing art_index"), 0);
    va_start(args, cols);
	i = 0;
	acc_cols = 0;
	max_rows = 0;
//	printf("[pt_art_print_in_columns] Debug 1\n");
	while (i < cols)
	{
		art[i] = va_arg(args, t_pt_ascii_art*);
		acc_cols += art[i]->size.ws_col;
		if (art[i]->size.ws_row / art[i]->ver_el > max_rows)
			max_rows = art[i]->size.ws_row / art[i]->ver_el;

		art_vindex[i] = va_arg(args, int);
		if (art_vindex[i] < 0 || art_vindex[i] >= art[i]->ver_el)
		{
			free(art);
			va_end(args);
			return (free(art_vindex),
					dprintf(STDERR_FILENO, "wrong index for art\n"), 0);
		}
		i++;
	}
    va_end(args);
	if (max_rows > max_size.ws_row)
	{
		free(art);
		return (free(art_vindex),
				dprintf(STDERR_FILENO, "won't fit screen, increas height\n"),
				0);
	}
	if (acc_cols + cols - 1 > max_size.ws_col)
	{
		free(art);
		return (free(art_vindex),
				dprintf(STDERR_FILENO, "won't fit screen, increase width\n"),
				0);
	}


	int	col_spacing;
	int	line;
	int	col;
	int	symbol_offset;
	int	symbol_i_offset;

	col_spacing = 1; // TODO auto
	line = 0;
	while (line < max_rows)
	{
		col = 0;
		while (col < cols)
		{
			symbol_offset = 1;
			symbol_offset *= art[col]->size.ws_col;
			symbol_offset *= art[col]->size.ws_row / art[col]->ver_el;
		   	symbol_i_offset = symbol_offset * art_vindex[col];
			pthread_mutex_lock(&pt->screen_mx);
			write(STDIN_FILENO,
					art[col]->data + symbol_i_offset + line * art[col]->size.ws_col,
					art[col]->size.ws_col);
			i = 0;
			while (i < col_spacing)
			{
				write(STDIN_FILENO, " ", 1);
				i++;
			}
			pthread_mutex_unlock(&pt->screen_mx); 
			col++;
		}
		pthread_mutex_lock(&pt->screen_mx); 
		write(STDIN_FILENO, "\n", 1);
		pthread_mutex_unlock(&pt->screen_mx); 
		line++;
	}
	free(art);
	free(art_vindex);
	return (1);
}
