/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/07 21:16:13 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int static void ft_color_iter(t_w *w, int px, int py)
**	Function to set black or white
** **************************************************************************
*/

static int		ft_color_iter(int i, int i_max)
{
	//int			w_mid;
	int			color;
	//printf("\n-------ft_color_iter start-------\n");
	if (i < i_max)
		return(0x000000);
	else
		return(0xFFFFFF);
	color = 0;
	//(i % 256, 255, 255 * (i < i_max)));
	//return(color);
	//printf("\n-------ft_color_iter end-------\n");
}

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
	double		zm;
	double		mv_x;
	double		mv_y;

	zm = w->fractols[w->f_type][0];
	mv_x = w->fractols[w->f_type][1];
	mv_y = w->fractols[w->f_type][2];
	w->x_scl = 1.5 * (px - w->width / 2) / (0.5 * zm * w->width) + mv_x;
    w->y_scl = (py - w->height / 2) / (0.5 * zm * w->height) + mv_y;
	//printf("sc_px=%f sc_py=%f\n", w->x_scl, w->y_scl);
	//printf("\n-------ft_crds_scale end-------\n");
}

/* -2.5 -2.4 -2.3 -2.2 -2.1 -2.0 -1.9
** **************************************************************************
**	static void ft_img_pxl_put(t_w *w, int px, int py)
**	Function to place one pixel into memory
** **************************************************************************
*/

static void		ft_img_pxl_put(t_w *w, int x, int y)
{
	int			i;

	//printf("\n-------ft_img_pxl_put start-------\n");
	//printf("x=%d, y=%d, bitspp=%d, ln_sz=%d\n", x, y, w->bitspp, w->ln_sz);
	i = (x * (w->bitspp / 8)) + (y * w->ln_sz);
	w->img[i] = w->color; // B — Blue
	w->img[++i] = w->color >> 8; // G — Green
	w->img[++i] = w->color >> 16; // R — Red
	w->img[++i] = 0;
	//printf("\n-------ft_img_pxl_put end-------\n");
}

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *w, int px, int py)
**	Function to analyze one pixel
** **************************************************************************
*/

static void		ft_pxl_analyze(t_w *w, int px, int py)
{
	int			i;
	int			max_i;
	double		x_tmp;
	double		y_tmp;
	double		x0;
	double		y0;
	double		x;
	double		y;

	//printf("\n-------ft_pxl_analize start-px1=%d py1=%d-\n", px, py);
	y_tmp = 0;
	i = 0;
	max_i = 50;
	x0 = w->x_scl;
	y0 = w->y_scl;
	x = 0.0;
	y = 0.0;
	while ((x*x + y*y <= 2*2)  &&  (i < max_i))
	{
		x_tmp = x;
		y_tmp = y;
		x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + w->x_scl;
 		y = (2 * x_tmp * y_tmp) + w->y_scl;
		i++;
	}
/* 
      //remember value of previous iteration
      oldRe = newRe;
      oldIm = newIm;
      //the actual iteration, the real and imaginary part are calculated
      newRe = oldRe * oldRe - oldIm * oldIm + pr;
      newIm = 2 * oldRe * oldIm + pi;
      //if the point is outside the circle with radius 2: stop
      if((newRe * newRe + newIm * newIm) > 4) break;
    }*/
	w->color = ft_color_iter(i, max_i);//0xFFF245;//ft_color_iter(i, max_i);
	ft_img_pxl_put(w, px, py);
	//printf("\n-------ft_pxl_analyze end-------\n");
}

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function to initialize window and image in struct t_w w
** **************************************************************************
*/

void			ft_draw(t_w *w)
{
	int			i;
	int			j;

	i = 0;
	printf("\n-------ft_draw start-------\n");
	while (i < w->width)
	{
		j = 0;
		while (j < w->height)
		{
			ft_crds_scale(w, i, j);
			ft_pxl_analyze(w, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);	
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
