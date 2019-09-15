/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/15 21:32:45 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_crds_scale(t_w *w, int px, int py)
**	Function to get
**	x0 = scaled x coord of pxl(scaled to lie in the Manbrt X scale(-2.5, 1));
**	y0 = scaled y coord of pxl(scaled to lie in the Manbrt Y scale(-1, 1));
** **************************************************************************
*/

void		ft_crds_scale(t_w *w, int px, int py)
{
	//printf("\n-------ft_crds_scale start-------\n");
	w->x_scl = 1.5 * (px - W_WIDTH / 2) / (0.5 * w->zm * W_WIDTH) + w->mv_x;
    w->y_scl = (py - W_HEIGHT / 2) / (0.5 * w->zm * W_HEIGHT) + w->mv_y;
	//printf("\n-------ft_crds_scale end-------\n");
}

/*
** **************************************************************************
**	void ft_thread_select(t_w *w, int i, int j, void (*f)())
**	Function for select fractol type from user input
** **************************************************************************
*/

void			ft_fractol_sel(t_pxl *pxl)
{
	if (pxl->w->f_type == 0)
		ft_mandelbrot(pxl);
/*	else if (w->f_type == 1)
		return(ft_julia);
	else if (w->f_type == 2)
		return(ft_koch);
	else if (w->f_type == 3)
		return(ft_sierpinski);
	else if (w->f_type == 4)
		return(ft_attractor);
	
*/
}

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

void			ft_draw(t_w *w)
{
	pthread_t	th_id[W_WIDTH];
	t_pxl		pxl;
//	int			*p;
	int			res;

	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	pxl.px = 0;
	pxl.py = 0;
	pxl.w = w;
	res = 1;
	while (pxl.px < W_WIDTH)
	{
		pxl.py = 0;
		if ((res = pthread_create(&th_id[pxl.px], NULL, ft_multi, &pxl)) || (res != 0))
		{
			ft_putstr_fd("Thread error", 2);
			exit(res);
		}
		//*p = (int)&th_id[pxl.px];
		//ft_putnbr(*p);
		pthread_join(th_id[pxl.px], NULL);
		pxl.px++;
	}
	
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_man(w);
	printf("-------ft_draw end-------\n");
}
//if ((res = pthread_create(&th_id[count], NULL, f, &pxl)) || (res != 0))
//ft_putstr_fd("Thread error", 2);
				//	exit(res);
/*
** **************************************************************************
**	void ft_thread_select(t_w *w, int i, int j, void (*f)())
**	Function for select thread for each pixel
** **************************************************************************
*/

void			*ft_multi(void *pxl_ptr)
{
//	pthread_t	th_id[W_HEIGHT - 1];
	t_pxl		*pxl;

	//printf("-------ft_multi start-------\n");
	pxl = (t_pxl*)pxl_ptr;
	while (pxl->py < W_HEIGHT)
	{
		/*if ((res = pthread_create(&th_id[pxl->py], NULL, ft_fractol_sel, &pxl)) || (res != 0))
		{
			ft_putstr_fd("Thread error", 2);
			exit(res);
		}
		*p = (int)&th_id[pxl.px];
		//ft_putnbr(*p);
		pthread_join(th_id[pxl->py], NULL);
		*/
		ft_fractol_sel(pxl);
		pxl->py++;
	}
	//printf("-------ft_multi end-------\n");

	return (NULL);
}
/*
*/

/*
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
** **************************************************************************
*/
