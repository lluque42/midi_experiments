/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ascii_art.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:29:27 by lluque            #+#    #+#             */
/*   Updated: 2025/06/16 00:26:48 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pt_ascii_art.h
 * The ascii arts used in this program were mainly generated from:
 * https://patorjk.com/software/taag/
 * (fonts: Colossal, Slant Relief)
 */

#ifndef PT_ASCII_ART_H
# define PT_ASCII_ART_H

# include "piano_trainer.h"

# define PT_LOGO_PATH "data/logo"
# define PT_ALTERATIONS_PATH "data/alterations_w12_h10"
# define PT_ANG_NOTES_PATH "data/anglo_notes_w24_h10"
# define PT_LAT_NOTES_PATH "data/latin_notes_w24_h10"
# define PT_NUMBERS_PATH "data/numbers_w12_h10"

/**
 * @struct s_pt_ascii_art
 * @brief Base for typedef <b>t_pt_ascii_art</b>.
 * @details
 * TODO.
 *
 * @var s_pt_ascii_art::size
 * Image size in chars (row, col). (type defined in ioctl-types.h)
 * @var s_pt_ascii_art::data
 * A linear array of chars with the image data. To get a line use this
 * addressing:
 * 		line_n = art->data[n * art->size.ws_col]
 * @var s_pt_ascii_art::ver_el
 * If more than one image is included in the data, this member indicates
 * how many there are vertically. For example, a value of 3 would be used for:
 *
 * A
 *
 * E
 *
 * I
 * @var s_pt_ascii_art::hor_el
 * If more than one image is included in the data, this member indicates
 * how many there are horizontaally. For example, a value of 3 would be used
 * for: A E I
 * @var s_pt_ascii_art::incl_nl
 * If 1, each line (every row -1) there's a \n character. This would allow to
 * printf() the data and render its content easily. However, it would difficult
 * the renderization of more than one ascii art one next to each other.
 */
typedef struct s_pt_ascii_art
{
	struct winsize	size;
	char			*data;
	int				ver_el;
	int				hor_el;
}	t_pt_ascii_art;
/**
 * @typedef t_pt_ascii_art
 * @brief Based on the @link s_pt_ascii_art @endlink struct.
 */

t_pt_ascii_art	*pt_art_load_art(char *path, int ver_el, int hor_el);

struct winsize	pt_art_get_art_size(char *path);

void			pt_art_print_dump(t_pt *pt, t_pt_ascii_art  *art);

int				pt_art_print_in_columns(t_pt *pt, struct winsize max_size,
											int cols, ...);

int				pt_art_init(t_pt *pt);

void			pt_art_destroy_art(t_pt_ascii_art *art);
/*

TRY                 YOUR GUESS         TIME LEFT

Note Alt            Note Alt           Second1 Second2

VVVVVVVVEEEEEEEEEERRRRRRRRRRDDDDDDDDIIIIIIICCCCCTTTTTTT




*/


#endif
