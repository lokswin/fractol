/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/18 18:43:48 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	Function to store five types of fractols
**	Mandelbrot, Julia,
**	0 - zoom
**	1 - move_x
**	2 - move_y
** **************************************************************************
*/

void		ft_init_arr_fractols(t_w *w)
{
	double	fractols[5][3];
	int		i;
	int		j;

	i = 0;
	fractols[0][0] = 1;
	fractols[0][1] = -0.5;
	fractols[0][2] = 0;
	w->zm = 1;
	w->mv_x = -0.5;
	w->mv_y = 0;
	w->b_clr = 0;
	w->g_clr = 0;
	w->r_clr = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			w->fractols[i][j] = fractols[i][j];
			j++;
		}
		i++;
	}
}

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	Function to get user map
** **************************************************************************
*/

int				main(int argc, char **argv)
{
	t_w			new_w;

	if (argc != 2)
	{
		ft_putstr("usage: ./fractol [fractol number]\n\n\
0 - Mandelbrot set;\n\
1 - Julia set;\n\
2 - Koch snowflake;\n\
3 - Sierpinski carpet;\n\
4 - Attractor;\n\
		\n");
		exit(1);
	}
	
	//int pthread_create(th_id, NULL, void *(*start_routine) (void *), void *arg);

	//int pthread_join(pthread_t thread, void **retval);

	//void pthread_exit(void *retval);


	new_w.f_type = ft_atoi(argv[1]);
	ft_putnbr(new_w.f_type);
	ft_new_win(&new_w);
	ft_init_arr_fractols(&new_w);
	ft_draw(&new_w);
	mlx_mouse_hook(new_w.win_p, ft_ui_mouse, &new_w);
	mlx_key_hook(new_w.win_p, ft_ui_keys, &new_w);
	mlx_loop(new_w.mlx_p);
	exit(0);
}
