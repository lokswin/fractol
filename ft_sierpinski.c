/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/06 20:00:39 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_sierpinski(t_param *p)
{
	int			y;
	int			tmp_x;
	int			x;
	int			i;
	t_fractol	f;

	i = 0;
	//printf("\n-------ft_mand start-px1=%d py1=%d-\n", p->w->px, p->w->py);
	mlx_clear_window(p->w->mlx_p, p->w->win_p);
	pthread_mutex_lock(&p->w->lock_x);
	//p->w->mv_x = p->w->mv_x + ((int)(p->w->mv_x) % 3));
	//p->w->mv_y = p->w->mv_y + ((int)(p->w->mv_x) % 3)) ;
	while (p->py_beg < p->py_end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			//p->w->x_scl = 1.5 * (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			//p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			p->w->x_scl = (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			f.x = p->w->x_scl;
			f.y = p->w->y_scl;
			if (!(p->py_beg % 759))
				printf("x=%d, p->py_beg=%d, p->w->mv_x=%d, p->w->mv_y=%d, p->w->zm=%d\n", x, p->py_beg, ((int)(trunc(p->w->mv_x* 9)) ), ((int)(trunc(p->w->mv_y* 9))), (int)(ceil(0.5 * p->w->zm)));
			//tmp_x = ((1.5 * (x - W_WIDTH / 2)) / (int)(ceil(0.5 * p->w->zm))) + ((int)(ceil(p->w->mv_x * 9)));
			//y = ((p->py_beg - W_HEIGHT / 2) / (int)(ceil(0.5 * p->w->zm))) + ((int)(ceil(p->w->mv_y * 9)));
			//tmp_x = (x / (int)(ceil(0.5 * p->w->zm))) + ((int)(trunc(p->w->mv_x * 9)));
			//y = (p->py_beg / (int)(ceil(0.5 * p->w->zm))) + ((int)(trunc(p->w->mv_y * 9)));
			//tmp_x = (int)(p->w->x_scl);
			//y = (int)(p->w->y_scl);
			tmp_x = x;
			y = p->py_beg;
			//tmp_x = (int)(f.x);
			//y = (int)(f.y);
			i = 0;
			while ((i < p->w->max_i) && (f.x > 0 || f.y > 0))
			{
				if (((int)(trunc(f.x)) % 3 == 1) && ((int)(trunc(f.y)) % 3 == 1))
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
	//printf("\n-------ft_pxl_analyze end-------\n");
}