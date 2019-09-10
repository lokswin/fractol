/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attractor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/10 17:24:07 by drafe            ###   ########.fr       */
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
	int			color;
	int			red;
	int			green;
	int			blue;
	double		t;
	
	//printf("\n-------ft_color_iter start-------\n");
	color = 0xFFFFFF;
	t = (double)i / (double)i_max;
	red = (int)(9 * (1 - t) * pow(t, 3) * 255);
	green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	//printf("r%d,g%d,b%d",red, green, blue);
	return(color);
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
	//double		zm;
	//double		mv_x;
	//double		mv_y;

	//printf("\n-------ft_crds_scale start-------\n");
	w->x_scl = 1.5 * (px - w->width / 2) / (0.5 * w->zm * w->width) + w->mv_x;
    w->y_scl = (py - w->height / 2) / (0.5 * w->zm * w->height) + w->mv_y;
	//printf("sc_px=%f sc_py=%f\n", w->x_scl, w->y_scl);
	//printf("\n-------ft_crds_scale end-------\n");
}

/* -2.5 -2.4 -2.3 -2.2 -2.1 -2.0 -1.9
** **************************************************************************
**	static void ft_img_pxl_put(t_w *w, int px, int py)
**	Function to place one pixel into memory
** **************************************************************************
*/

static void		ft_img_pxl_put(t_w *w, int x, int y, int i, int i_max)
{
	int			j;
	double		t;

	//printf("\n-------ft_img_pxl_put start-------\n");
	//printf("x=%d, y=%d, bitspp=%d, ln_sz=%d\n", x, y, w->bitspp, w->ln_sz);
	t = (double)i / (double)i_max;
	j = (x * (w->bitspp / 8)) + (y * w->ln_sz);
	w->img[j] = (int)(9 * (1 - t) * pow(t, 3) * 255);//w->color; // B — Blue
	w->img[++j] = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255) >> 8;//w->color >> 8; // G — Green
	w->img[++j] = (int)(8.5 * pow((1 - t), 3) * t * 255) >> 16;//w->color >> 16; // R — Red
	w->img[++j] = 0;
	//printf("\n-------ft_img_pxl_put end-------\n");
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
	int			max_i;
	double		re;
	double		im;
	double		x0;
	double		y0;
	double		x;
	double		y;

	//printf("\n-------ft_pxl_analize start-px1=%d py1=%d-\n", px, py);
	i = 0;
	max_i = 50;
	x0 = w->x_scl;
	y0 = w->y_scl;
	x = 0.0;
	y = 0.0;
	while ((x*x + y*y <= 2*2)  &&  (i < max_i))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + w->x_scl;
 		y = (2 * re * im) + w->y_scl;
		i++;
	}
	w->color = ft_color_iter(i, max_i);//0xFFF245;//ft_color_iter(i, max_i);
	ft_img_pxl_put(w, px, py, i, max_i);
	//printf("\n-------ft_pxl_analyze end-------\n");
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
	printf("\n-------ft_draw start--zm%f--x%f--y%f-\n", w->zm, w->mv_x, w->mv_y);
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
