/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/15 20:42:34 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_sierpinski(t_param *p)
{
	int			x;
	int			i;
	t_fractol	f;

	pthread_mutex_lock(&p->w->lock_x);
	while ((++p->py_beg < p->py_end) && (x = -1))
		while ((++x < W) && (i = -1))
		{
			f.x = (x - W / 2) / (0.5 * p->w->zm * W) + p->w->mv_x;
			f.y = (p->py_beg - H / 2) / (0.5 * p->w->zm * H) + p->w->mv_y;
			while ((++i < p->w->max_i) && (f.x > 0 || f.y > 0))
			{
				if (((int)(f.x) % 3 == 1) && ((int)(f.y) % 3 == 1))
					break ;
				f.x = f.x / 3;
				f.y = f.y / 3;
			}
			ft_img_pxl_put(p->w, x, p->py_beg, i);
		}
	pthread_mutex_unlock(&p->w->lock_x);
	pthread_exit(NULL);
}
