/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_art_print_dump.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:11:38 by lluque            #+#    #+#             */
/*   Updated: 2025/06/15 16:20:50 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

void	pt_art_print_dump(t_pt_ascii_art  *art)
{
	int	index;

	index = 0;
	while (index < art->size.ws_row)
	{
		write(STDIN_FILENO,
				art->data + index * art->size.ws_col, art->size.ws_col);
		write(STDIN_FILENO, "\n", 1);
		index++;
	}
}

int	pt_art_print_in_columns(struct winsize max_size, int cols, ...)
{
	va_list			args;
	t_pt_ascii_art	**art;
	int				i;
	int				acc_cols;
	int				max_rows;
	int				*art_vindex;

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
	while (i < cols)
	{
		art[i] = va_arg(args, t_pt_ascii_art*);
		acc_cols += art[i]->size.ws_col;
		if (art[i]->size.ws_row / art[i]->ver_el > max_rows)
			max_rows = art[i]->size.ws_row / art[i]->ver_el;

		art_vindex[i] = va_arg(args, int);
		printf("for art[%d] rows = %d cols = %d ver_el = %d desired element %d\n",
				i,
				art[i]->size.ws_row,
				art[i]->size.ws_col,
				art[i]->ver_el,
				art_vindex[i]);
		if (art_vindex[i] < 0 || art_vindex[i] >= art[i]->ver_el)
		{
			free(art); // And its members... TODO
			va_end(args);
			return (dprintf(STDERR_FILENO, "wrong index for art\n"), 0);
		}

//	printf("******************** [pt_art_print_in_columns] ****************\n");
//	printf("Will b printed from this:\n");
//	printf("\tIn column %d\n the element %d\n", i, art_vindex[i]);
//	pt_art_print_dump(art[i]);
//	printf("******************** [pt_art_print_in_columns] ****************\n");
		i++;
	}
    va_end(args);
	if (max_rows > max_size.ws_row)
	{
		free(art); // And its members... TODO
		return (dprintf(STDERR_FILENO, "won't fit screen, increas height\n"), 0);
	}
	if (acc_cols + cols - 1 > max_size.ws_col)
	{
		free(art); // And its members... TODO
		return (dprintf(STDERR_FILENO, "won't fit screen, increase width\n"), 0);
	}


	int	col_spacing;
	int	line;
	int	col;
//	char	*first_char;

	col_spacing = 1; // TODO auto
	printf ("max_rows %d\n", max_rows);
	line = 0;
	//while (col < cols)
	while (line < max_rows)
	{
//		printf ("\tline %d\n", line);
		col = 0;
		while (col < cols)
		{
//			printf ("\t\tcol %d\n", col);
			
			int	symbol_offset;

//			printf("Art base pointer %p\n", art[col]->data);
			symbol_offset = 1;
			symbol_offset *= art[col]->size.ws_col;
			symbol_offset *= art[col]->size.ws_row / art[col]->ver_el;
//			printf("Per symbol offset (in chars) = %d\n", symbol_offset);
			
			int	symbol_i_offset;

		   	symbol_i_offset = symbol_offset * art_vindex[col];
//			printf("Total offset (in chars) = %d\n", symbol_i_offset);
//			first_char = symbol_i_offset + art[col]->data;
//			printf("Pointer end value = %p\n", first_char);

			write(STDIN_FILENO,
					//art[col]->data + art[col]->size.ws_col * line,
					art[col]->data + symbol_i_offset + line * art[col]->size.ws_col,
					art[col]->size.ws_col);
			i = 0;
			while (i < col_spacing)
			{
				write(STDIN_FILENO, " ", 1);
				i++;
			}
			col++;
		}
		write(STDIN_FILENO, "\n", 1);
		line++;
	}
	free(art); // And its members... TODO
	return (1);
}
