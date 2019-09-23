/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/23 21:58:24 by drafe            ###   ########.fr       */
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

void			ft_fractol_select(t_w *w, int x, int y)
{
	if (w->f_type == 0)
		ft_mandelbrot(w, x, y);
	else if ((w->f_type == 1 )|| (w->f_type == 11))
		ft_julia(w, x, y);
/*	else if (w->f_type == 2)
		return(ft_koch);
	else if (w->f_type == 3)
		return(ft_sierpinski);
	else if (w->f_type == 4)
		return(ft_attractor);
	
*/
}

/*
** **************************************************************************
**	static void ft_thread_run(t_w *w)
**	Function for run on thread
** **************************************************************************
*/

static void		ft_thread_run(t_w *w)
{
	pthread_t		tid[w->threads + 1];
	pthread_attr_t	attr;
	int				res;

	if ((res = pthread_attr_init(&attr)) || (res != 0))
	{
		ft_putstr_fd("pthread_attr_init error", 2);
		exit(res);
	}
	if ((res = pthread_create(&tid[w->flow], &attr, ft_multi, (void*)w)) || (res != 0))
	{
		ft_putstr_fd("pthread_create error", 2);
		exit(res);
	}
	if ((res = pthread_join(tid[w->flow], NULL)) || (res != 0))
	{
		ft_putstr_fd("pthread_join error", 2);
		exit(res);
	}
}

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

int				ft_draw(t_w *w)
{
	clock_t		t;
	double		time_taken;

	t = clock();
	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	w->px = 0;
	w->last_px = 0;
	while (w->px < W_WIDTH)
	{
		w->py = 0;
		w->flow = 0;
		while (w->flow < w->threads)
		{
			ft_thread_run(w);
			//ft_multi((void*)w);
		}
		//while (w->flow < w->threads)
		//{
			//ft_thread_run(w);
			//ft_multi2((void*)w);
		//}
		w->px++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_man(w);
	t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("\ntime_taken = %f\n", time_taken);
	printf("-------ft_draw end-------\n");
	return (1);
}

/*
** **************************************************************************
**	void ft_thread_select(t_w *w, int i, int j, void (*f)())
**	Function for select thread for each pixel
** **************************************************************************
*/

void			*ft_multi(void *w_ptr)
{
	t_w		*w;
	int		tmp_x;
	int		tmp_y;
	int		step;
	
	w = (t_w*)w_ptr;
	tmp_x = 0;
	
	step = W_HEIGHT / w->threads;
	w->last_px = step * (w->flow + 1);
	w->py = step * w->flow;
	tmp_y = w->py;
	w->flow++;
	//printf("######## ft_multi start w->px=%d w->py=%d w->last_px=%d w->flow=%d\n", w->px, tmp_y, w->last_px, w->flow);
	while (tmp_y < w->last_px)
	{
		ft_fractol_select(w, w->px, tmp_y);
		tmp_y++;
	}
	//printf("######## ft_multi end ########\n");
	return (NULL);
}

void			*ft_multi2(void *w_ptr)
{
	t_w		*w;
	int		tmp_x;
	int		tmp_y;
	int		step;
	
	w = (t_w*)w_ptr;
	tmp_x = 0;
	
	step = W_HEIGHT / w->threads;
	w->last_px = step * (w->flow + 1);
	w->py = step * w->flow;
	tmp_y = w->py;
	w->flow++;
	printf("######## ft_multi2 start w->px=%d w->py=%d w->last_px=%d w->flow=%d\n", w->px, tmp_y, w->last_px, w->flow);
	while (tmp_y < w->last_px)
	{
		ft_fractol_select(w, w->px, tmp_y);
		tmp_y++;
	}
	//printf("######## ft_multi end ########\n");
	return (NULL);
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
