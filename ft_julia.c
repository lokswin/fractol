/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/06 20:52:37 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *w, int px, int py)
**	Function to draw Julia set
** **************************************************************************
*/

void		ft_julia(t_param *p)
{
//	int			y;
	int			x;
	int			i;
	t_fractol	f;

	i = 0;
	//printf("\n-------ft_mand start-px1=%d py1=%d-\n", p->w->px, p->w->py);
	pthread_mutex_lock(&p->w->lock_x);
	while (p->py_beg < p->py_end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			p->w->x_scl = 1.5 * (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			f.x = p->w->x_scl;
			f.y = p->w->y_scl;
			i = 0;
			while ((f.x * f.x + f.y * f.y <= 4)  &&  (i < p->w->max_i))
			{
				f.re = f.x;
				f.im = f.y;
				f.x = (f.re * f.re) - (f.im * f.im) + p->w->j_cre;
 				f.y = (2 * f.re * f.im) + p->w->j_cim;
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
