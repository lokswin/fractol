/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand_walk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/15 21:04:11 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_rand_walk(t_param *p)
{
	int			x;
	int			i;
	t_fractol	f;

	pthread_mutex_lock(&p->w->lock_x);
	while ((++p->py_beg < p->py_end) && (x = -1))
		while ((++x < W) && (i = -1))
		{
			p->w->x_scl = 1.5 * (x - W / 2) / (0.5 * p->w->zm * H) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - H / 2) / (0.5 * p->w->zm * H) \
			+ p->w->mv_y;
			f.x = (rand() % 10000) / 500.0 - 10;
			f.y = (rand() % 10000) / 500.0 - 10;
			while ((f.x * f.x + f.y * f.y <= 10000) && (++i < p->w->max_i))
			{
				f.re = f.x;
				f.im = f.y;
				f.x = (f.re / cos(f.im)) + p->w->j_cre;
				f.y = (f.im / sin(f.re)) + p->w->j_cim;
			}
			ft_img_pxl_put(p->w, x, p->py_beg, i);
		}
	pthread_mutex_unlock(&p->w->lock_x);
	pthread_exit(NULL);
}
