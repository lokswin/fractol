/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/15 20:49:39 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_julia(t_param *p)
{
	int			x;
	int			i;
	t_fractol	f;

	i = 0;
	pthread_mutex_lock(&p->w->lock_x);
	while ((++p->py_beg < p->py_end) && (x = -1))
		while ((++x < W) && (i = -1))
		{
			p->w->x_scl = 1.5 * (x - W / 2) / (0.5 * p->w->zm * W) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W / 2) / (0.5 * p->w->zm * H) \
			+ p->w->mv_y;
			f.x = p->w->x_scl;
			f.y = p->w->y_scl;
			while ((f.x * f.x + f.y * f.y <= 4) && (++i < p->w->max_i))
			{
				f.re = f.x;
				f.im = f.y;
				f.x = (f.re * f.re) - (f.im * f.im) + p->w->j_cre;
				f.y = (2 * f.re * f.im) + p->w->j_cim;
			}
			ft_img_pxl_put(p->w, x, p->py_beg, i);
		}
	pthread_mutex_unlock(&p->w->lock_x);
	pthread_exit(NULL);
}
