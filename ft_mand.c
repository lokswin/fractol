/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/25 20:41:41 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_mand(t_w *w, int px, int py)
{
	int			i;
	double		re;
	double		im;
	double		x;
	double		y;

	i = 0;
	x = 0.0;
	y = 0.0;
	//printf("\n-------ft_mand start-px1=%d py1=%d-\n", px, py);
	ft_crds_scale(w, px, py);
	while ((x*x + y*y <= 2*2)  &&  (i < w->max_i))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + w->x_scl;
 		y = (2 * re * im) + w->y_scl;
		i++;
	}
	ft_img_pxl_put(w, px, py, i);
	//printf("\n-------ft_mand end-------\n");
}
