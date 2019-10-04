/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_burning_ship.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/03 21:36:25 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_burning_ship(t_param *p)
{
	int			x;
	int			i;
	t_fractol	f;

	//printf("\n-------ft_burning_ship start-beg=%d end1=%d-\n", p->py_beg, p->py_end);
	pthread_mutex_lock(&p->w->lock_x);
	while (p->py_beg < p->py_end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			p->w->x_scl = 1.5 * (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			f.x = 0;
			f.y = 0;
			i = 0;
			while ((f.x * f.x + f.y * f.y <= 4) &&  (i < p->w->max_i ))
			{
				f.re = f.x;
				f.im = f.y;
				f.x = fabs((f.re * f.re) - (f.im * f.im) + p->w->x_scl);
				f.y = fabs((2 * f.re * f.im) + p->w->y_scl);
				i++;
			}
			ft_img_pxl_put(p->w, x, p->py_beg, i);
			x++;
		}
		p->py_beg++;
	}
	pthread_mutex_unlock(&p->w->lock_x);
	pthread_exit(NULL);
	//printf("\n-------ft_burning_ship end-------\n");
}
