/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_koch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/06 22:05:10 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_koch(t_param *p)
{
	int			x;
   double a = 10.0;
   double b = 28.0;
   double c = 8.0 / 3.0;

	int			i;
	t_fractol	f;

	//printf("\n-------ft_koch start-beg=%d end1=%d-\n", p->py_beg, p->py_end);
	a = p->w->j_cre; b = p->w->j_cim; c = p->w->c;

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
			//f.x = 0;
			//f.y = 0;
			//printf("r=%f\n", r);
			i = 0;
			while ((i < p->w->max_i))
			{
				f.re = f.x;
				f.im = f.y;
				f.x = (f.re * f.re) - (f.im * f.im) + p->w->x_scl;
				f.y = (2 * f.re * f.im) + p->w->y_scl;
				//printf("f.x=%f f.y=%f f.re=%f f.im=%f sum=%f\n", f.x, f.y, f.re, f.im, f.x * f.x + f.y * f.y);
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

/*f.re = f.x;
				f.im = f.y;
				//xn+1 = yn - sign(xn) | b xn - c |1/2
				//yn+1 = a - xn
					a = 1; b = 4; c = 60;
					a = 2; b = -1; c = 200;
					a = 10; b = -10; c = 0.01;
					a = 31; b = 12; c = 0.5;
					a = 0.1; b = 0.1; c = 10;
					a = 10; b = 1, c = 60;
				f.x = f.im - (((f.re > 0) ? 1 : ((f.re < 0) ? -1 : 0)) * pow(fabs(b * f.re - c), 1/2)); //+ p->w->x_scl;
 				f.y = a - f.re; //+ p->w->y_scl;
				 //(((f.re > 0) ? 1 : ((f.re < 0) ? -1 : 0))*/
				 /*if (r < 0.01) 
				{
					f.x =  0;
					f.y =  0.16 * f.im;
				}
				else if (r < 0.86)
				{
					f.x =  0.85 * f.re + 0.04 * f.im;
					f.y = -0.04 * f.re + 0.85 * f.im + 1.6;
				}
				else if (r < 0.93)
				{
					f.x =  0.20 * f.re - 0.26 * f.im;
					f.y =  0.23 * f.re + 0.22 * f.im + 1.6;
				}
				else
				{
					f.x = -0.15 * f.re + 0.28 * f.im;
					f.y =  0.26 * f.re + 0.24 * f.im + 0.44;
				}
				len = len / sqrt(2);
				f.re = f.x;
				f.im = f.y;
				if (!(i % 4))
					alp += 0.785398;
				else
					alp += -0.785398;
				f.x = (f.re * f.re) - (f.im * f.im) + (len * cos(0.785398 + alp));
				f.y = (2 * f.re * f.im) + (len * sin(0.785398 + alp));*/
			/*	 length = (length / Math.sqrt(2));
            c_curve(x, y, length, (alpha + default_angle), (iteration - 1), ctx ); // Recursive Call
            x = (x + (length * Math.cos(toRadians(alpha + default_angle))));
            y = (y + (length * Math.sin(toRadians(alpha + default_angle))));
            c_curve(x, y, length, (alpha - default_angle), (iteration - 1), ctx ); */