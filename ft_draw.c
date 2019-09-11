/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/11 21:04:39 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int static void ft_crds_scale(t_w *w, int px, int py)
**	Function to get
**	x0 = scaled x coord of pxl(scaled to lie in the Manbrt X scale(-2.5, 1));
**	y0 = scaled y coord of pxl(scaled to lie in the Manbrt Y scale(-1, 1));
** **************************************************************************
*/

static void		ft_crds_scale(t_w *w, int px, int py)
{
	//double		zm;
	//double		mv_x;
	//double		mv_y;

	//printf("\n-------ft_crds_scale start-------\n");
	w->x_scl = 1.5 * (px - w->width / 2) / (0.5 * w->zm * w->width) + w->mv_x;
    w->y_scl = (py - w->height / 2) / (0.5 * w->zm * w->height) + w->mv_y;
	//printf("sc_px=%f sc_py=%f\n", w->x_scl, w->y_scl);
	//printf("\n-------ft_crds_scale end-------\n");
}

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *w, int px, int py)
**	Function to analyze one pixel
** **************************************************************************
*/

static void		ft_mandelbrot(t_w *w, int px, int py)
{
	int			i;
	double		re;
	double		im;
	double		x;
	double		y;

	//printf("\n-------ft_pxl_analize start-px1=%d py1=%d-\n", px, py);
	i = 0;
	x = 0.0;
	y = 0.0;
	while ((x*x + y*y <= 2*2)  &&  (i < w->max_i))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + w->x_scl;
 		y = (2 * re * im) + w->y_scl;
		i++;
	}
	//w->color = 
	ft_color_iter(i, w->max_i);//0xFFF245;//ft_color_iter(i, max_i);
	ft_img_pxl_put(w, px, py, i);
	//printf("\n-------ft_pxl_analyze end-------\n");
}

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

void			ft_draw(t_w *w)
{
	int			i;
	int			j;

	i = 0;
	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	while (i < w->width)
	{
		j = 0;
		while (j < w->height)
		{
			ft_crds_scale(w, i, j);
			ft_mandelbrot(w, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);	
	ft_draw_man(w);
	printf("-------ft_draw end-------\n");
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
