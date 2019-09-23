/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/23 21:23:34 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		ft_putman(void)
{
	ft_putstr("usage: ./fractol [fractol number]\n\n\
	0 - Mandelbrot set;\n\
	1 - Julia set;\n\
	2 - Koch snowflake;\n\
	3 - Sierpinski carpet;\n\
	4 - Attractor;\n\
	\n");
}

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

	if ((argc != 2))
	{
		ft_putman();
		exit(1);
	}
	if ((new_w.f_type = ft_atoi(argv[1])) > 4)
	{
		ft_putman();
		exit(1);
	}
	ft_new_win(&new_w);
	ft_init_arr_fractols(&new_w);
	ft_draw(&new_w);
	mlx_hook(new_w.win_p, 6, 32, ft_mouse_mv, (void*)(&new_w));
	mlx_mouse_hook(new_w.win_p, ft_ui_mouse, (void*)&new_w);
	mlx_key_hook(new_w.win_p, ft_ui_keys, (void*)&new_w);
	mlx_loop(new_w.mlx_p);
	exit(0);
}
