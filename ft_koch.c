/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_koch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/04 20:29:40 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_koch(t_param *p)
{
//	int			y;
//	int			z;
	int			x;
	int			i;
	int			tmp;
//	double		x2;
//	double		y2;
	t_fractol	f;

	//printf("\n-------ft_koch start-beg=%d end1=%d-\n", p->py_beg, p->py_end);
	pthread_mutex_lock(&p->w->lock_x);
	printf("j_cim=%f\n", p->w->j_cim);
	while (p->py_beg < p->py_end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			p->w->x_scl = 1.5 * (x - W_WIDTH / 2) / (0.5 * p->w->zm * W_WIDTH) + p->w->mv_x;
			p->w->y_scl = (p->py_beg - W_HEIGHT / 2) / (0.5 * p->w->zm * W_HEIGHT) + p->w->mv_y;
			f.x = x * 0.005;//-0.7;
			f.y = p->py_beg * 0.005;//0.5;
			f.x = p->w->x_scl;
			f.y = p->w->y_scl;
			i = 0;
			f.re = f.x;
			f.im = f.y;
/*//d := z;
		p3 = (point)
		x2	(2*p1.x+p2.x)/3,
		y2	(2*p1.y+p2.y)/3};
		
		p5 = (point)
		re{(2*p2.x+p1.x)/3,
		im(2*p2.y+p1.y)/3};

		p4 = (point){p3.x + (p5.x - p3.x)*cos(theta) + (p5.y - p3.y)*sin(theta),
					p3.y - (p5.x - p3.x)*sin(theta) + (p5.y - p3.y)*cos(theta)};*/
			while (((sqrt(f.x)+sqrt(f.y) < 1e+6) && (sqrt(f.re)+sqrt(f.im) > 1e-6)) &&  (i < p->w->max_i))
			{
				f.re = f.x;
				f.im = f.y;
				//z = f.re + f.y * p->w->j_cim;
				//f.x = ((3 * pow(z, 4)) + 1) / (4 * pow(z, 3));
				//f.y = ((3 * pow(z, 4)) + 1) / (4 * pow(z, 3));
				/*z.x := X * 0.005;
					z.y := Y * 0.005;
					d := z;
					while (sqr(z.x)+sqr(z.y) < max) and (sqr(d.x)+sqr(d.y) > min)
						and (n < iter) do	begin
				t := z;
				{z^3 - 1}
				p := sqr(sqr(t.x)+sqr(t.y));
				z.x := 2/3*t.x + (sqr(t.x)-sqr(t.y))/(3*p);
				z.y := 2/3*t.y*(1-t.x/p);{}
				d.x := abs(t.x - z.x);
				d.y := abs(t.y - z.y);
				Inc(n);*/
				tmp = sqrt(sqrt(f.re) + sqrt(f.im));
				f.x = (2/3 * f.re + (sqrt(f.re) - sqrt(f.im))) / (3 * tmp);
				f.y = 2/3 * f.im * ((1 - f.re) / tmp);
				f.re = fabs(f.re - f.x);
				f.im = fabs(f.im - f.y);
				//f.y = ((3 * pow(f.im, 4)) + 1) / (4 * pow(f.im, 3));
				//Z[i+1] = Z[i] * Z[i] + C,
				//f.x = (f.re * f.re) - (f.im * f.im) + p->w->x_scl;
				//f.y = (2 * f.re * f.im) + p->w->y_scl;
				//printf("p->w->j_cim=%f\n", p->w->j_cim);
				//printf("f.x=%f f.y=%f  f.re=%f f.im=%f\n", f.x, f.y, f.re, f.im);
				//printf("f.x=%f f.y=%f  f.re=%f f.im=%f sum=%f\n", f.x, f.y, f.re, f.im, (f.x * f.x + f.y * f.y));
				//z = z^(2) / (1 + z + z^(4)) + constant z^(2) / (1 + z + z^(4))
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
/*
GLfloat oldx=-0.7,oldy=0.5;

void drawkoch(GLfloat dir,GLfloat len,GLint iter) {
	GLdouble dirRad = 0.0174533 * dir;  
	GLfloat newX = oldx + len * cos(dirRad);
	GLfloat newY = oldy + len * sin(dirRad);
	if (iter==0) {
		glVertex2f(oldx, oldy);
		glVertex2f(newX, newY);
		oldx = newX;
		oldy = newY;
	}
	else {
		iter--;
		//draw the four parts of the side _/\_ 
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
		dir -= 120.0;
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
	}
}

void kochCurve(point p1,point p2,int times){
	point p3,p4,p5;
	double theta = pi/3;
 
	if(times>0){
		p3 = (point){(2*p1.x+p2.x)/3,(2*p1.y+p2.y)/3};
		p5 = (point){(2*p2.x+p1.x)/3,(2*p2.y+p1.y)/3};
 
		p4 = (point){p3.x + (p5.x - p3.x)*cos(theta) + (p5.y - p3.y)*sin(theta),p3.y - (p5.x - p3.x)*sin(theta) + (p5.y - p3.y)*cos(theta)};
 
		kochCurve(p1,p3,times-1);
		kochCurve(p3,p4,times-1);
		kochCurve(p4,p5,times-1);
		kochCurve(p5,p2,times-1);
	}
 
	else{
		line(p1.x,p1.y,p2.x,p2.y);
	}
}

*/