/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/15 21:35:58 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_putman(void)
**	Function for print man
** **************************************************************************
*/

void				ft_putman(void)
{
	ft_putstr("\nusage: ./fractol [fractol number]\n\n\
	0 - Mandelbrot set;\n\
	1 - Julia set;\n\
	2 - Fish;\n\
	3 - Tricorn;\n\
	4 - Carpet;\n\
	5 - Sierpinski carpet;\n\
	6 - Henon;\n\
	7 - Burning ship;\n\
	8 - Random walk;\n\
	9 - Self call;\n\
	\n");
}

/*
** **************************************************************************
**	static void *ft_fractol_select(void *w_ptr)
**	Function for select fractol type from user input
** **************************************************************************
*/

static void			*ft_fractol_select(void *w_ptr)
{
	t_param			*p;

	p = (t_param*)w_ptr;
	if (p->w->f_type == 0)
		ft_mand(p);
	if ((p->w->f_type == 1) || (p->w->f_type == 11))
		ft_julia(p);
	if (p->w->f_type == 2)
		ft_mand_fish(p);
	if (p->w->f_type == 3)
		ft_mand_tricorn(p);
	if (p->w->f_type == 4)
		ft_carpet(p);
	if (p->w->f_type == 5)
		ft_sierpinski(p);
	if (p->w->f_type == 6)
		ft_henon(p);
	if (p->w->f_type == 7)
		ft_burning_ship(p);
	if (p->w->f_type == 8)
		ft_rand_walk(p);
	if (p->w->f_type == 9)
		ft_self_call(p);
	return (NULL);
}

/*
** **************************************************************************
**	static void ft_thread_run(t_w *w)
**	Function for run on thread
** **************************************************************************
*/

static void			ft_thread_run(t_w *w)
{
	pthread_t		tid[w->threads];
	∫B
	int				i;

	pthread_mutex_init(&w->lock_x, NULL);
	i = 0;
	w->px = 0;
	w->py = 0;
	while (i < w->threads)
	{
		p[i].w = w;
		p[i].py_beg = (H / w->threads) * i - 1;
		p[i].py_end = (H / w->threads) * (i + 1);
		if(pthread_create(&tid[i], NULL, ft_fractol_select, (void*)&p[i]) != 0)
		{
			ft_putstr_fd("pthread_create error", 2);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < w->threads)
	{
		if(pthread_join(tid[i], NULL) != 0)
		{
			ft_putstr_fd("pthread_join error", 2);
			exit(1);
		}
		i++;
	}
}

/*
** **************************************************************************
**	void ft_draw(t_w *w)
**	Function for draw picture
** **************************************************************************
*/

void				ft_draw(t_w *w)
{
	int				i;
	clock_t			t;
	double			time_taken;
	int				j;

	i = 0;
	j = 0;
	t = clock();
	ft_thread_run(w);
	while (i < 320)
	{
		j = W - 20;
		while (j < H)
		{
			ft_img_pxl_put(w, i, j, 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(w->mlx_p, w->win_p, w->img_p, 0, 0);
	ft_draw_iter(w);
	t = clock() - t;
	time_taken = (double)t / CLOCKS_PER_SEC;
	printf("\ntime_taken = %f\n", time_taken);
}
