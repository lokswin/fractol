/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/07 19:32:35 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int static void ft_crds_scale(t_w *new_w, int px, int py)
**	Function to get
**	x0 = scaled x coord of pxl(scaled to lie in the Manbrt X scale(-2.5, 1));
**	y0 = scaled y coord of pxl(scaled to lie in the Manbrt Y scale(-1, 1));
** **************************************************************************
*/

static void		ft_crds_scale(t_w *new_w, int px, int py)
{
	//int			w_mid;
	//int			h_mid;
	printf("\n-------ft_crds_scale start-------\n");
	new_w->x_scale = 1.5 * (px - new_w->width / 2) / (0.5 * new_w->zm * new_w->width) + new_w->mv_x;
    new_w->y_scale = (py - new_w->height / 2) / (0.5 * new_w->zm * new_w->height) + new_w->mv_y;
	printf("sc_px=%d sc_py=%d", new_w->x_scale, new_w->y_scale);
	printf("\n-------ft_crds_scale end-------\n");
}

/* -2.5 -2.4 -2.3 -2.2 -2.1 -2.0 -1.9 
** **************************************************************************
**	int static void ft_pxl_analize(t_w *new_w, int px, int py)
**	Function to place one pixel into memory
** **************************************************************************
*/

static void		ft_img_pxl_put(t_w *new_w, int x, int y)
{
	int			i;

	printf("\n-------ft_img_pxl_put start-------\n");
	printf("x=%d, y=%d, bitspp=%d, ln_sz=%d\n", x, y, new_w->bitspp, new_w->ln_sz);
	i = (x * (new_w->bitspp / 8)) + (y * new_w->ln_sz);
	new_w->img[i] = new_w->color; // B — Blue
	new_w->img[++i] = new_w->color >> 8; // G — Green
	new_w->img[++i] = new_w->color >> 16; // R — Red
	new_w->img[++i] = 0;
	printf("\n-------ft_img_pxl_put end-------\n");
}

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *new_w, int px, int py)
**	Function to analyze one pixel
** **************************************************************************
*/

static void		ft_pxl_analyze(t_w *new_w, int px, int py)
{
	int			i;
	int			max_i;
	int			x_tmp;
	int			x0;
	int			y0;
	int			x;
	int			y;

	printf("\n-------ft_pxl_analize start-px1=%d py1=%d-\n", px, py);
	i = 0;
	max_i = 50;
	x0 = new_w->x_scale;
	y0 = new_w->y_scale;
	x = 0.0;
	y = 0.0;
	while ((x*x + y*y <= 2*2)  &&  (i < max_i))
	{
		x_tmp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = x_tmp;
 		i++;
	}
	new_w->color = 0xFFFFFF;
	ft_img_pxl_put(new_w, px, py);
	printf("\n-------ft_pxl_analyze end-------\n");
}

/*
** **************************************************************************
**	void ft_draw(t_w *new_w)
**	Function to initialize window and image in struct t_w new_w
** **************************************************************************
*/

void			ft_draw(t_w *new_w)
{
	int			i;
	int			j;

	i = 0;
	printf("\n-------ft_draw start-------\n");
	mlx_key_hook(new_w->win_p, ft_ui_keys, new_w);


	while (i < new_w->width)
	{
		j = 0;
		while (j < new_w->height)
		{
			ft_crds_scale(new_w, i, j);
			ft_pxl_analyze(new_w, i, j);
			j++;
		}
		i++;
	}
	mlx_loop(new_w->mlx_p);
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
