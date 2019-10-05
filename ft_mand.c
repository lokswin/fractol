/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/04 21:48:18 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_mand(t_param *p)
{
//	int			y;
	int			x;
	int			i;
	t_fractol	f;

	//printf("\n-------ft_mand start-px1=%d py1=%d-\n", p->w->px, p->w->py);
	pthread_mutex_lock(&p->w->lock_x);
	while (p->py_beg < p->py_end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			p->w->x_scl = 1.5 * (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			f.x = 0.0;
			f.y = 0.0;
			i = 0;
			while ((f.x * f.x + f.y * f.y <= 4)  &&  (i < p->w->max_i))
			{
				f.re = f.x;
				f.im = f.y;
				f.x = (f.re * f.re) - (f.im * f.im) + p->w->x_scl;
				f.y = (2 * f.re * f.im) + p->w->y_scl;
				i++;
			}
			ft_img_pxl_put(p->w, x, p->py_beg, i);
			x++;
		}
		p->py_beg++;
	}
	pthread_mutex_unlock(&p->w->lock_x);
	pthread_exit(NULL);
	//printf("\n-------ft_mand end-------\n");
}
		