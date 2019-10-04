/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/04 19:23:31 by drafe            ###   ########.fr       */
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
**	void ft_fr_select(t_w *w, int i, int j, void (*f)())
**	Function for select fractol type from user input
** **************************************************************************
*/

void			*ft_fractol_select(void *w_ptr)
{
	t_param		*p;

	p = (t_param*)w_ptr;
	if (p->w->f_type == 0)
		ft_mand(p);
	if ((p->w->f_type == 1) || (p->w->f_type == 11))
		ft_julia(p);
	if (p->w->f_type == 2)
		ft_koch(p);
	if (p->w->f_type == 5)
		ft_burning_ship(p);	
	//printf("\n######## ft_fractol_select thread=%d x=%d y=%d\n", ((int)pthread_self()), p->w->px, p->w->py);
	//printf("######## ft_fractol_select end ########\n");
	return (NULL);
}
	
/*
** **************************************************************************
**	static void ft_thread_run(t_w *w)
**	Function for run on thread
** **************************************************************************
*/

static void		ft_thread_run(t_w *w)
{
	pthread_t			tid[w->threads];
	t_param				p[w->threads];
	int					i;
	int					res;

	//printf("######## ft_thread_run start ########\n");
	pthread_mutex_init(&w->lock_x, NULL);
	i = 0;
	w->px = 0;
	w->py = 0;
	res = 0;
	while(i < w->threads)
	{
		w->px = 0;
		w->py = 0;
		p[i].w = w;
		p[i].py_beg = (W_HEIGHT / w->threads) * i;
		p[i].py_end = (W_HEIGHT / w->threads) * (i + 1);
		pthread_create(&tid[i], NULL, ft_fractol_select, (void*)&p[i]);
		i++;
	}
	i = 0;
	while (i < w->threads)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	//printf("######## ft_thread_run end ########\n");
}

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for pixel iteration
** **************************************************************************
*/

int					ft_draw(t_w *w)
{
	int				i;
	clock_t			t;
	double			time_taken;
	int				j;

	i = 0;
	j = 0;
	t = clock();
	printf("\n-------ft_draw start--zm=%f x=%f y=%f\n", w->zm, w->mv_x, w->mv_y);
	ft_thread_run(w);
	while (i < 320)
	{
		j = W_HEIGHT - 20;
		while (j < W_HEIGHT)
		{
			ft_img_pxl_put(w, i, j, 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_iter(w);
	t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("\ntime_taken = %f\n", time_taken);
	printf("-------ft_draw end-------\n");
	return (1);
}

/*	
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
**	if o1 then o2 else o3		o1 ? o2 : o3
** **************************************************************************
*/
