/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/17 20:47:19 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_zoom(t_w *w, int *x, int *y)
**	Function to zoom with mouse
** **************************************************************************
*/

static void		ft_zoom(t_w *w, int *x, int *y)
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
	if ((key == 5) || (key == 4))// 5 4
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

int		ft_ui_keys(int key, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	if (key == PLUS_KEY)
	{
		w->max_i += 50;
		ft_draw(w);
	}
	if (key == MINUS_KEY)
	{
		w->max_i -= 50;
		ft_draw(w);
	}
	if (key == SPACE)
	{
		w->max_i = 100;
		ft_init_arr_fractols(w);
		ft_draw(w);
	}
	if ((key == R_KEY) || (key == G_KEY) || (key == B_KEY))
		ft_change_color(w, key);
	if ((key == ARROW_U) || (key == ARROW_D) || (key == ARROW_R) || (key == ARROW_L))
		ft_move_shape(w, key);
	if ((key == NUM_2) || (key == NUM_4) || (key == NUM_6) || (key == NUM_8))
		ft_change_shape(w, key);
	if (key == ESC)
		exit(0);
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
	G - change greeb color\n\
	B - change blue color\n\
	SPACE - default set\n\
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
