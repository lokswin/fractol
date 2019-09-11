/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/11 21:17:48 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_zoom(t_w *w, int *x, int *y)
**	Function to zoom with mouse
** **************************************************************************
	//ZOOM keys
    if(keyDown(SDLK_KP_PLUS))  {zoom *= pow(1.001, 1);}
    if(keyDown(SDLK_KP_MINUS)) {zoom /= pow(1.001, 1);}
*/

static void		ft_zoom(t_w *w, int *x, int *y)
{
	double		old_zm;
	double		offs_x;
	double		offs_y;
	//double		dzm;
	
	old_zm = w->zm;
	w->zm *= pow(1.001, 1000);
	//dzm = w->zm - old_zm;
	offs_x = 1.5 * (*x - w->width / 2) / (0.5 * old_zm * w->width) + w->mv_x;
	offs_y = (*y - w->height / 2) / (0.5 * old_zm * w->height) + w->mv_y;
	w->mv_x = offs_x;
	w->mv_y = offs_y;
	//printf("x=%f y=%f offs_x=%f offs_y=%f\n",w->mv_x, w->mv_y, offs_x, offs_y);
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
	ft_putnbr(key);
	if ((key == 1) || (key == 2))// 5 4
	{
		ft_putstr("\nZooming...");
		if (key == 2)
			ft_zoom(w, &x, &y);
		else
			w->zm /= pow(1.001, 1000);
		ft_draw(w);
		printf("%fdone!", w->zm);
	}
	return ((int)param);
}
/*
	//new_w->mv_x += ((new_w->width / (-2)) + x) / (10 * new_w->zm);
	//new_w->mv_y += ((new_w->width / 2) - y) / (10 * new_w->zm);
	//new_w->zm / (new_w->width - y);
    //ZOOM keys
    if(keyDown(SDLK_KP_PLUS))  {zoom *= pow(1.001, 1);}
    if(keyDown(SDLK_KP_MINUS)) {zoom /= pow(1.001, 1);}
*/

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
	ft_putnbr(key);
	if (key == 69)
	{
		w->max_i += 50;
		ft_draw(w);
	}
	if (key == 78)
	{
		w->max_i -= 50;
		ft_draw(w);
	}
	if (key == 49)
	{
		w->max_i = 100;
		ft_init_arr_fractols(w);
		ft_draw(w);
	}
	if ((key == 15) || (key == 5) || (key == 11))
		ft_change_color(w, key);
	if ((key == 123) || (key == 124) || (key == 125) || (key == 126))
		ft_move_shape(w, key);
	if ((key == 91) || (key == 84) || (key == 86) || (key == 88))
		ft_change_shape(w, key);
	if (key == 53)
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
	new_w->win_p = mlx_new_window(new_w->mlx_p, new_w->width, new_w->height, "Fractol");
	ft_putstr("Fractol man:\n\
	ESC : quit Fractol");
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
