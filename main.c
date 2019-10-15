/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/15 18:40:04 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		ft_putman();
		exit(1);
	}
	if ((new_w.f_type = ft_atoi(argv[1])) > 11)
	{
		ft_putman();
		exit(1);
	}
	ft_new_win(&new_w);
	ft_draw(&new_w);
	mlx_hook(new_w.win_p, 3, 1L << 1, ft_keyrelease, (void*)&new_w);
	mlx_hook(new_w.win_p, 2, 1L << 0, ft_ui_keys, (void*)&new_w);
	mlx_mouse_hook(new_w.win_p, ft_ui_mouse, (void*)&new_w);
	mlx_hook(new_w.win_p, 6, 1L << 6, ft_mouse_mv, (void*)(&new_w));
	mlx_loop(new_w.mlx_p);
	exit(0);
}
