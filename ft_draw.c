/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/21 21:15:18 by drafe            ###   ########.fr       */
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
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

void				ft_draw(t_w *w)
{
	pthread_t		tid[w->w_threads*2 + 1];
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
	w->flow = 0;
	step = W_WIDTH / (w->w_threads);
	w->last_px = step;
	while (w->flow < w->w_threads * 2)
	{
		//w->last_px = step * (w->flow + 1);
		//w->px = step * w->flow;
		//printf("i=%d w->px=%d w->last_px=%d \n", i, w->px, w->last_px);
		//if ((printf("1") || !ft_multi((void*)w)))
		// 	;
		//if ((w->last_px = step * (i + 1)) && ft_multi2((void*)w))
		//	;
		//w->flow++;
		printf("f=%d\n", w->flow);
		ft_multi2((void*)w);
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
/*		if ((res = pthread_join(tid[w->flow], NULL)) || (res != 0))
		{
			ft_putstr_fd("pthread_join error", 2);
			exit(res);
		}
		ft_multi((void*)w);
		printf("f=%d\n", w->flow);
		//w->px = w->last_px;
		//w->last_px += step;
		//w->px = w->last_px;
		//w->last_px += step;
		*/
	}
	w->flow = 0;
	while (w->flow < w->w_threads * 2)
	{
		pthread_join(tid[w->flow], NULL);
		/* if ((res = pthread_join(tid[w->flow], NULL)) || (res != 0))
		{
			ft_putstr_fd("pthread_join error", 2);
			exit(res);
		}*/
		w->flow++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_man(w);
	t = clock() - t; 
    time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("\ntime_taken = %f\n", time_taken);
	printf("-------ft_draw end-------\n");
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
	step = W_WIDTH / (w->w_threads * 2);//(w->w_threads * 2);
	w->last_px = step * (w->flow + 1);
	w->px = step * w->flow;
	w->flow++;
	tmp_x = w->px;
	printf("######## ft_multi start w->px=%d w->last_px=%d \n", tmp_x, w->last_px);
	while((tmp_x < w->last_px) && (tmp_x < W_WIDTH))
	{
		tmp_y = 0;
		while (tmp_y < W_HEIGHT)
		{
			ft_fractol_select(w, tmp_x, tmp_y);
			tmp_y++;
		}
		tmp_x++;
	}
	
	printf("######## ft_multi end ########\n");
	return (NULL);
}


void			*ft_multi(void *w_ptr)
{
	t_w		*w;
	int		tmp_x;
	int		tmp_y;
	int		step;
	
	w = (t_w*)w_ptr;
	step = W_WIDTH / (w->w_threads * 2);//(w->w_threads * 2);
	w->last_px = step * (w->flow + 1);
	w->px = step * w->flow;
	w->flow++;
	tmp_x = w->px;
	printf("######## ft_multi start w->px=%d w->last_px=%d \n", tmp_x, w->last_px);
	while((tmp_x < w->last_px) && (tmp_x < W_WIDTH))
	{
		tmp_y = 0;
		while (tmp_y < W_HEIGHT)
		{
			ft_fractol_select(w, tmp_x, tmp_y);
			tmp_y++;
		}
		tmp_x++;
	}
	
	printf("######## ft_multi end ########\n");
	return (NULL);
}

void			*ft_multi2(void *w_ptr)
{
	t_w		*w;
	int		tmp_x;
	int		tmp_y;
	int		step;
	
	w = (t_w*)w_ptr;
	step = W_WIDTH / (w->w_threads * 2);//(w->w_threads * 2);
	w->last_px = step * (w->flow + 1);
	w->px = step * w->flow;
	w->flow++;
	tmp_x = w->px;
	printf("######## ft_multi2 start w->px=%d w->last_px=%d \n", tmp_x, w->last_px);
	while((tmp_x < w->last_px) && (tmp_x < W_WIDTH))
	{
		tmp_y = 0;
		while (tmp_y < W_HEIGHT)
		{
			ft_fractol_select(w, tmp_x, tmp_y);
			tmp_y++;
		}
		tmp_x++;
	}
	
	printf("######## ft_multi2 end ########\n");
	return (NULL);
}




//if ((w->px == w->last_px) && (w->last_px == step))
//	w->px = step;
//w->last_px += step;
//w->px = tmp_x;
//w->px = w->px + step;
	//w->px += step;
/*	
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
** **************************************************************************
*/
