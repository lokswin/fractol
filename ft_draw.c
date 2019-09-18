/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/18 18:52:59 by drafe            ###   ########.fr       */
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

void			ft_fractol_select(t_w *w)
{
	if (w->f_type == 0)
		ft_mandelbrot(w);
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

void				ft_draw(t_w *w)
{
	pthread_t		tid[10];
	pthread_attr_t	attr;
	int				step;
	int				i;
	int				res;
	clock_t		t;
	double		time_taken;

	t = clock();
	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	w->px = 0;
	res = 1;
	i = 0;
	step = W_WIDTH / 10;
	w->last_px = step;
	while (i < 9)
	{
		if ((res = pthread_attr_init(&attr)) || (res != 0))
		{
			ft_putstr_fd("pthread_attr_init error", 2);
			exit(res);
		}
		if ((res = pthread_create(&tid[i], &attr, ft_multi, w)) || (res != 0))
		{
			ft_putstr_fd("pthread_create error", 2);
			exit(res);
		}
		w->px = w->last_px;
		w->last_px += step;
		
	//	ft_multi(w);
	//	w->last_px += step;
		i++;
	}
	i = 0;
	while(i < 9)
	{
		if ((res = pthread_join(tid[i], NULL)) || (res != 0))
		{
			ft_putstr_fd("pthread_join error", 2);
			exit(res);
		}
		i++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_man(w);
	t = clock() - t; 
    time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("\ntime_taken = %f\n", time_taken);
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

void			*ft_multi(void *w_ptr)
{
	t_w		*w;
	int		tmp;
	
	w = (t_w*)w_ptr;
	tmp = w->px;
	printf("######## ft_multi start w->px=%d w->last_px=%d w->py=%d\n", w->px, w->last_px, w->py);
	while(tmp < w->last_px)
	{
		w->py = 0;
		while (w->py < W_HEIGHT)
		{
			ft_fractol_select(w);
			w->py++;
		}
		tmp++;
	}
	printf("######## ft_multi end ########\n");
	//pthread_exit(NULL);
	return (NULL);
}
	//printf("%d,\n", w->px);
/*	
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
** **************************************************************************
*/
