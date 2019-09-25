/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/25 22:14:50 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_zoom(t_w *w, int *x, int *y)
**	Function to zoom with mouse
** **************************************************************************
*/

void		ft_zoom(t_w *w, int *x, int *y)
{
	double		offs_x;
	double		offs_y;

	offs_x = 1.5 * (*x - W_WIDTH / 2) / (0.5 * w->zm * W_WIDTH) + w->mv_x;
	offs_y = (*y - W_HEIGHT / 2) / (0.5 * w->zm * W_HEIGHT) + w->mv_y;
	w->mv_x = offs_x;
	w->mv_y = offs_y;
	w->zm *= pow(1.001, 1000);
}

/*
** **************************************************************************
**	int ft_ui_mouse(int key, int x, int y, void *param)
**	Function to handle mouse input
** **************************************************************************
*/

int			ft_ui_mouse(int key, int x, int y, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	if (w->f_type == 1)
	{
		w->m_x = x;
		w->m_y = y;
	}
	if ((key == 5) || (key == 4))
	{
		ft_putstr("\nZooming...");
		if (key == 5)
			ft_zoom(w, &x, &y);
		else
			w->zm /= pow(1.001, 1000);
		ft_draw(w);
		ft_putstr("%zooming done!");
	}
	return ((int)param);
}

/*
** **************************************************************************
**	int ft_ui_keys(int key, void *param)
**	Function to handle key input
** **************************************************************************
*/

static void ft_ui_keys_exp(t_w *w, int key)
{
	if (key == MINUS_KEY)
		w->max_i -= 50;
	if (key == PLUS_KEY)
		w->max_i += 50;
	if (key == SPACE)
	{
		if (w->f_type == 11)
			w->f_type = 1;
		ft_w_layout(w);
	}
	if ((key == P_KEY) && ((w->threads + 2) <= 32))
		w->threads += 200;
	if ((key == I_KEY) && ((w->threads - 2) >= 2))
		w->threads -= 200;
	ft_draw(w);
}

/*
** **************************************************************************
**	int ft_ui_keys(int key, void *param)
**	Function to handle key input
** **************************************************************************
*/

int		ft_ui_keys(int key, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	if (key == ESC)
		exit(0);
	if ((key == PLUS_KEY) || (key == MINUS_KEY) || (key == SPACE) || \
	(key == ESC) || (key == P_KEY) || (key == I_KEY) || (key == O_KEY))
		ft_ui_keys_exp(w, key);
	if ((key == A_KEY) && (w->f_type == 1))
		w->f_type = 11;
	if ((key == S_KEY) && (w->f_type == 11))
		w->f_type = 1;
	if ((key == R_KEY) || (key == G_KEY) || (key == B_KEY) || (key == C_KEY))
		ft_change_color(w, key);
	if ((key == ARROW_U) || (key == ARROW_D) || (key == ARROW_R) || (key == ARROW_L))
		ft_move_shape(w, key);
	if ((key == NUM_2) || (key == NUM_4) || (key == NUM_6) || (key == NUM_8))
		ft_change_shape(w, key);
	return ((int)param);
}

/*
** **************************************************************************
**	void ft_ui(t_w *new_w)
**	Function to create win_p
** **************************************************************************
*/

void		ft_ui(t_w *new_w)
{
	printf("\n-------ft_ui start-------\n");
	new_w->win_p = mlx_new_window(new_w->mlx_p, W_WIDTH, W_HEIGHT, "Fractol");
	ft_putstr("Fractol man:\n\
	ESC : quit Fractol\n\
	R - change red color\n\
	G - change green color\n\
	B - change blue color\n\
	C - rainbow\n\
	SPACE - default\n\
	NUM(+) - add 50 iterations\n\
	NUM(-) - remove 50 iterations\n\
	");
	printf("-------ft_ui end-------\n");
}

/*
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
** **************************************************************************
*/
