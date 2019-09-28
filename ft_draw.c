/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/28 21:38:50 by drafe            ###   ########.fr       */
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

void			*ft_fractol_select(void *w_ptr)
{
	t_param		*p;
	int			max_pxl;
	int			px;
	int			py;
	int			step;

	//printf("######## ft_fractol_select\n");
	p = (t_param*)w_ptr;
	pthread_mutex_lock(&p->w->lock_x);
	px = p->pflow;
	step = W_WIDTH / p->w->threads;
	max_pxl = step * (p->pflow + 1);
	px = step * p->pflow;
	//printf("######## ft_fractol_select w->px=%d w->py=%d max_pxl=%d p->pflow=%d\n", p->w->px, p->w->py, max_pxl, p->pflow);
	while (px < max_pxl)
	{
		py = 0;
		while (py < W_HEIGHT)
		{
			if (p->w->f_type == 0)
				ft_mand(p->w, px, py);
			else if ((p->w->f_type == 1) || (p->w->f_type == 11))
				ft_julia(p->w, px, py);
			py++;
		}
		px += 1;//p->w->threads;
	}
	//printf("######## ft_fractol_select w->px=%d w->py=%d w->last_px=%d w->flow=%d\n", p->w->px, p->w->py, p->w->last_px, p->pflow);
	//printf("######## ft_fractol_select end ########\n");
	pthread_mutex_unlock(&p->w->lock_x);
	//if (!(p->pflow % 2))
	//	pthread_exit(NULL);
	return (NULL);
}

/*	x = thread_param->pixel_start;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel(param, x, y);
			y += 1;
		}
		x += THREADS_NUM;
	} */
	
/*
** **************************************************************************
**	static void ft_thread_run(t_w *w)
**	Function for run on thread
** **************************************************************************
*/

static pthread_t		*ft_thread_run(t_w *w)
{
	pthread_t			tid[w->threads];
	pthread_t			*ptr;
	pthread_attr_t 		attr;
	t_param				p[w->threads];
	int					i;
	int					res;

	//printf("######## ft_thread_run start ########\n");
	i = 0;
	res = 0;
	pthread_mutex_init(&w->lock_x, NULL);
	pthread_attr_init(&attr);
	while (i < w->threads)
	{
		pthread_attr_init(&attr);
		p[i].pflow = i;
		p[i].w = w;
		//ft_fractol_select((void*)&p[i]);
		pthread_create(&tid[i], &attr, ft_fractol_select, (void*)&p[i]);
		//ft_fractol_select((void*)&p[i]);
		 i++;
		p[i].pflow = i;
		p[i].w = w;
		//pthread_create(&tid[i], &attr, ft_fractol_select, (void*)&p[i]);
		ft_fractol_select((void*)&p[i]);/**/
		i++;
	}
	i = 0;
	while (i < w->threads)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	ptr = tid;
	return(ptr);
	//printf("######## ft_thread_run end ########\n");
}
/* 
	pthread_t		t[THREADS_NUM];
	t_thread_param	p[THREADS_NUM];
	int				i;

	i = 0;
	while (i < THREADS_NUM)
	{
		p[i].pixel_start = i;
		p[i].p = param;
		pthread_create(&t[i], NULL, func, &p[i]);
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(t[i], NULL);
		i++;
	}*/
/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

int					ft_draw(t_w *w)
{
	pthread_t		*tid2;
	int				i;
	clock_t			t;
	double			time_taken;
	
	i = 0;
	t = clock();
	w->px = 0;
	w->py = 0;
	w->last_px = 0;
	w->flow = 1;
	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	ft_thread_run(w);
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_man(w);
	t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("\ntime_taken = %f\n", time_taken);
	printf("-------ft_draw end-------\n");
	return (1);
	tid2 = ft_thread_run(w);
}

/*
** **************************************************************************
**	void ft_thread_select(t_w *w, int i, int j, void (*f)())
**	Function for select thread for each pixel
** **************************************************************************


void			*ft_multi(void *w_ptr)
{
	t_w		*w;
	int		tmp_x;
	int		tmp_y;
	int		step;
	
	w = (t_w*)w_ptr;
	tmp_x = 0;
	step = W_HEIGHT / w->threads;
	//w->last_px = step * (w->flow + 1);
	//w->py = step * w->flow;
	tmp_y = w->py;
	w->py++;
	//printf("######## ft_multi start w->px=%d w->py=%d w->last_px=%d w->flow=%d\n", w->px, tmp_y, w->last_px, w->flow);
	ft_fractol_select(w, w->px, tmp_y);
	tmp_y++;
	}
	//printf("######## ft_multi end ########\n");
	return (NULL);
}
*/
/**/
void			*ft_multi2(void *w_ptr)
{
	t_param		*p;
	int			tmp_x;
	int			tmp_y;

	p = (t_param*)w_ptr;
	printf("######## ft_fractol_select2 w->px=%d w->py=%d w->last_px=%d w->flow=%d\n", p->w->px, p->w->py, p->w->last_px, p->pflow);
	tmp_x = p->pflow;
	while (tmp_x < W_WIDTH)
	{
		tmp_y = 0;
		while (tmp_y < W_HEIGHT)
		{
			if (p->w->f_type == 0)
				ft_mand(p->w, tmp_x, tmp_y);
			else if ((p->w->f_type == 1 ) || (p->w->f_type == 11))
				ft_julia(p->w, tmp_x, tmp_y);
			tmp_y += 1;
		}
		tmp_x += p->w->threads;
	}
	//printf("######## ft_fractol_select end ########\n");
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
