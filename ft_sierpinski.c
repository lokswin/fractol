/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/08 19:01:19 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_sierpinski(t_param *p)
{
	int			x;
	int			i;
	t_fractol	f;

	i = 0;
	//printf("\n-------ft_sierpinski start-px1=%d py1=%d-\n", p->w->px, p->w->py);
	pthread_mutex_lock(&p->w->lock_x);
	while (p->py_beg < p->py_end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			p->w->x_scl = (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			f.x = p->w->x_scl;
			f.y = p->w->y_scl;
			i = 0;
			while ((i < p->w->max_i) && (f.x > 0 || f.y > 0))
			{
				if (((int)(f.x) % 3 == 1) && ((int)(f.y) % 3 == 1))
            		break;
        		f.x = f.x / 3;
        		f.y = f.y / 3;
				i++;
			}
			ft_img_pxl_put(p->w, x, p->py_beg, i);
			x++;
		}
		p->py_beg++;
	}
	pthread_mutex_unlock(&p->w->lock_x);
	pthread_exit(NULL);
	//printf("\n-------ft_sierpinski end-------\n");
}