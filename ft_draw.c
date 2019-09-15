/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/15 18:29:59 by drafe            ###   ########.fr       */
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
	//printf("\n-------ft_crds_scale start-------\n");
	w->x_scl = 1.5 * (px - w->width / 2) / (0.5 * w->zm * w->width) + w->mv_x;
    w->y_scl = (py - w->height / 2) / (0.5 * w->zm * w->height) + w->mv_y;
	//printf("\n-------ft_crds_scale end-------\n");
}

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *w, int px, int py)
**	Function to analyze one pixel
** **************************************************************************
*/

static void		ft_mandelbrot(void *pxl_ptr)
{
	int			i;
	double		re;
	double		im;
	double		x;
	double		y;
	t_pxl		*pxl;

	//printf("\n-------ft_pxl_analize start-px1=%d py1=%d-\n", px, py);
	i = 0;
	x = 0.0;
	y = 0.0;
	pxl = (t_pxl*)pxl_ptr;
	ft_crds_scale(pxl->w, pxl->px, pxl->py);
	while ((x*x + y*y <= 2*2)  &&  (i < pxl->w->max_i))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + pxl->w->x_scl;
 		y = (2 * re * im) + pxl->w->y_scl;
		i++;
	}
	ft_color_iter(i, pxl->w->max_i);
	ft_img_pxl_put(pxl->w, pxl->px, pxl->py, i);
	//printf("\n-------ft_pxl_analyze end-------\n");
}
/*static void		ft_mandelbrot(void *pxl_ptr)
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
	while ((x*x + y*y <= 2*2)  &&  (i < pxl_ptr.w.i_max))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + w->x_scl;
 		y = (2 * re * im) + w->y_scl;
		i++;
	}
	ft_color_iter(i, w->max_i);
	ft_img_pxl_put(w, px, py, i);
	//printf("\n-------ft_pxl_analyze end-------\n");
}*/

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

void			ft_draw(t_w *w)
{
	pthread_t	th_id;
	t_pxl		pxl;
	void		*f;
	int			res;

	pxl.px = 0;
	pxl.py = 0;
	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	f = ft_fractol_sel(w);
	while (pxl.px < w->width)
	{
		pxl.py = 0;
		while (pxl.py < w->height)
		{
			ft_thread_select(w, pxl.px, pxl.py, f);
			if (!(res = pthread_create(&th_id, NULL, f, &pxl)))
			{
				ft_putstr_fd("Thread error", 2);
				exit(res);
			}
			pthread_exit(NULL);
			pxl.py++;
		}
		pxl.px++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_man(w);
	printf("-------ft_draw end-------\n");
}

/*
** **************************************************************************
**	void ft_thread_select(t_w *w, int i, int j, void (*f)())
**	Function for select thread for each pixel
** **************************************************************************
*/

void			ft_thread_select(t_w *w, int i, int j, void (*f)())
{
	pthread_t	th_id;
	t_pxl		pxl;
	int			res;
	int			i;

	i = 4;
	res = 1;
	pxl.px = i;
	pxl.py = j;
	pxl.w = w;

	if (!(res = pthread_create(&th_id, NULL, f, &pxl)))
	{
		ft_putstr_fd("Thread error", 2);
		exit(res);
	}
			
    pthread_exit(NULL);
}

/*
** **************************************************************************
**	void ft_thread_select(t_w *w, int i, int j, void (*f)())
**	Function for select fractol type from user input
** **************************************************************************
*/

void			*ft_fractol_sel(t_w *w)
{
	if (w->f_type == 0)
		return(ft_mandelbrot);
/*	if (w->f_type == 1)
		return(ft_julia);
	if (w->f_type == 2)
		return(ft_koch);
	if (w->f_type == 3)
		return(ft_sierpinski);
	if (w->f_type == 4)
		return(ft_attractor);
*/
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
